// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2019-2025, The OpenROAD Authors

#include "Clustering.h"

#include <sys/timeb.h>

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>
#include <utility>
#include <vector>

#include "lemon/core.h"
#include "lemon/list_graph.h"
#include "lemon/maps.h"
#include "lemon/network_simplex.h"
#include "utl/Logger.h"


// Algorithms below belong to this production translation unit.
#include "LearningMode.h"
#include "LearningPolicyConfig.h"

// BEGIN INTEGRATED KERNEL Geometry
// SPDX-License-Identifier: BSD-3-Clause
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <vector>

namespace ord::learning {
struct Point
{
  double x = 0;
  double y = 0;
  std::size_t id = 0;
};

inline double manhattan(const Point& a, const Point& b)
{
  return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

inline double squaredDistance(const Point& a, const Point& b)
{
  const double dx = a.x - b.x;
  const double dy = a.y - b.y;
  return dx * dx + dy * dy;
}

struct Bounds
{
  double xmin = std::numeric_limits<double>::infinity();
  double ymin = std::numeric_limits<double>::infinity();
  double xmax = -std::numeric_limits<double>::infinity();
  double ymax = -std::numeric_limits<double>::infinity();

  void extend(const Point& p)
  {
    xmin = std::min(xmin, p.x);
    ymin = std::min(ymin, p.y);
    xmax = std::max(xmax, p.x);
    ymax = std::max(ymax, p.y);
  }

  bool empty() const { return xmin > xmax || ymin > ymax; }

  double lowerBound(const Point& p) const
  {
    if (empty()) {
      return std::numeric_limits<double>::infinity();
    }
    const double dx = std::max({xmin - p.x, 0.0, p.x - xmax});
    const double dy = std::max({ymin - p.y, 0.0, p.y - ymax});
    return dx + dy;
  }

  bool intersects(const Bounds& b) const
  {
    return !empty() && !b.empty() && xmin <= b.xmax && b.xmin <= xmax
           && ymin <= b.ymax && b.ymin <= ymax;
  }
};

inline std::uint64_t spreadBits(std::uint32_t value)
{
  std::uint64_t v = value;
  v = (v | (v << 16)) & 0x0000ffff0000ffffULL;
  v = (v | (v << 8)) & 0x00ff00ff00ff00ffULL;
  v = (v | (v << 4)) & 0x0f0f0f0f0f0f0f0fULL;
  v = (v | (v << 2)) & 0x3333333333333333ULL;
  return (v | (v << 1)) & 0x5555555555555555ULL;
}

inline std::uint64_t mortonKey(const Point& p, const Bounds& bounds)
{
  const auto quantize = [](double value, double low, double high) {
    if (high <= low) {
      return std::uint32_t{0};
    }
    const double normalized = std::clamp((value - low) / (high - low), 0.0, 1.0);
    return static_cast<std::uint32_t>(normalized * 65535.0);
  };
  return spreadBits(quantize(p.x, bounds.xmin, bounds.xmax))
         | (spreadBits(quantize(p.y, bounds.ymin, bounds.ymax)) << 1);
}

inline std::vector<Point> convexHull(std::vector<Point> points)
{
  std::sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
    return a.x != b.x ? a.x < b.x : a.y < b.y;
  });
  points.erase(std::unique(points.begin(), points.end(), [](const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
  }), points.end());
  if (points.size() <= 2) {
    return points;
  }
  const auto cross = [](const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
  };
  std::vector<Point> hull;
  for (const auto& point : points) {
    while (hull.size() >= 2 && cross(hull[hull.size() - 2], hull.back(), point) <= 0) {
      hull.pop_back();
    }
    hull.push_back(point);
  }
  const auto lower = hull.size();
  for (auto i = points.rbegin() + 1; i != points.rend(); ++i) {
    while (hull.size() > lower && cross(hull[hull.size() - 2], hull.back(), *i) <= 0) {
      hull.pop_back();
    }
    hull.push_back(*i);
  }
  hull.pop_back();
  return hull;
}
}  // namespace ord::learning
// END INTEGRATED KERNEL Geometry

// BEGIN INTEGRATED KERNEL KdTree
// SPDX-License-Identifier: BSD-3-Clause
#include <numeric>
#include <utility>

namespace ord::learning {
// Balanced spatial index with exact Manhattan nearest-neighbor queries.
class KdTree
{
 public:
  explicit KdTree(std::vector<Point> points) : points_(std::move(points))
  {
    for (const auto& p : points_) {
      if (!std::isfinite(p.x) || !std::isfinite(p.y)) {
        throw std::invalid_argument("KdTree requires finite coordinates");
      }
    }
    nodes_.reserve(points_.size());
    root_ = build(0, points_.size(), 0);
  }

  std::pair<double, std::size_t> nearest(
      const Point& query,
      std::size_t excluded = std::numeric_limits<std::size_t>::max()) const
  {
    std::pair<double, std::size_t> best{
        std::numeric_limits<double>::infinity(),
        std::numeric_limits<std::size_t>::max()};
    search(root_, query, excluded, best);
    return best;
  }

  std::vector<std::size_t> range(const Bounds& bounds) const
  {
    std::vector<std::size_t> ids;
    visit(root_, bounds, ids);
    std::sort(ids.begin(), ids.end());
    return ids;
  }

 private:
  struct Node
  {
    Point point;
    Bounds bounds;
    int left = -1;
    int right = -1;
  };

  int build(std::size_t begin, std::size_t end, unsigned depth)
  {
    if (begin == end) {
      return -1;
    }
    const auto middle = begin + (end - begin) / 2;
    const bool x_axis = depth % 2 == 0;
    std::nth_element(points_.begin() + begin, points_.begin() + middle,
                     points_.begin() + end, [x_axis](const Point& a, const Point& b) {
      const double av = x_axis ? a.x : a.y;
      const double bv = x_axis ? b.x : b.y;
      return av != bv ? av < bv : a.id < b.id;
    });
    const int index = static_cast<int>(nodes_.size());
    nodes_.push_back({points_[middle], {}, -1, -1});
    Bounds box;
    for (auto i = begin; i < end; ++i) {
      box.extend(points_[i]);
    }
    const int left = build(begin, middle, depth + 1);
    const int right = build(middle + 1, end, depth + 1);
    nodes_[index] = {points_[middle], box, left, right};
    return index;
  }

  void search(int index, const Point& query, std::size_t excluded,
              std::pair<double, std::size_t>& best) const
  {
    if (index < 0) {
      return;
    }
    const auto& node = nodes_[index];
    if (node.bounds.lowerBound(query) > best.first) {
      return;
    }
    if (node.point.id != excluded) {
      best = std::min(best, std::make_pair(manhattan(query, node.point), node.point.id));
    }
    int first = node.left;
    int second = node.right;
    if (first >= 0 && second >= 0
        && nodes_[second].bounds.lowerBound(query) < nodes_[first].bounds.lowerBound(query)) {
      std::swap(first, second);
    }
    search(first, query, excluded, best);
    search(second, query, excluded, best);
  }

  void visit(int index, const Bounds& box, std::vector<std::size_t>& ids) const
  {
    if (index < 0 || !nodes_[index].bounds.intersects(box)) {
      return;
    }
    const auto& n = nodes_[index];
    if (n.point.x >= box.xmin && n.point.x <= box.xmax
        && n.point.y >= box.ymin && n.point.y <= box.ymax) {
      ids.push_back(n.point.id);
    }
    visit(n.left, box, ids);
    visit(n.right, box, ids);
  }

  std::vector<Point> points_;
  std::vector<Node> nodes_;
  int root_ = -1;
};
}  // namespace ord::learning
// END INTEGRATED KERNEL KdTree

namespace cts::CKMeans {

using lemon::INVALID;
using lemon::ListDigraph;
using lemon::NetworkSimplex;
using utl::CTS;

struct Sink
{
  Sink(const float x, const float y, const unsigned idx)
      : x(x), y(y), sink_idx(idx)
  {
  }

  // location
  const float x, y;
  int cluster_idx{-1};
  const unsigned sink_idx;  // index in sinks_
};

Clustering::Clustering(const std::vector<std::pair<float, float>>& sinks,
                       utl::Logger* logger)
{
  logger_ = logger;
  sinks_.reserve(sinks.size());
  for (size_t i = 0; i < sinks.size(); ++i) {
    sinks_.emplace_back(sinks[i].first, sinks[i].second, i);
  }
}

Clustering::Clustering(const std::vector<std::pair<float, float>>& sinks,
                       const float xBranch,
                       const float yBranch,
                       utl::Logger* logger)
    : Clustering(sinks, logger)
{
  branching_point_ = {xBranch, yBranch};
  srand(56);
}

Clustering::~Clustering() = default;

/*** Capacitated K means **************************************************/
void Clustering::iterKmeans(const unsigned iter,
                            const unsigned n,
                            const unsigned cap,
                            const unsigned max,
                            const unsigned power,
                            std::vector<std::pair<float, float>>& means)
{
  const unsigned midIdx = means.size() / 2 - 1;
  segment_length_ = std::abs(means[midIdx].first - means[midIdx + 1].first)
                    + std::abs(means[midIdx].second - means[midIdx + 1].second);

  std::vector<int> solution(sinks_.size());
  float max_silh = -1;
  auto tmp_means = means;
  for (unsigned i = 0; i < iter; ++i) {
    const float silh = Kmeans(n, cap, max, power, tmp_means);
    if (silh > max_silh) {
      max_silh = silh;
      for (size_t j = 0; j < sinks_.size(); ++j) {
        solution[j] = sinks_[j].cluster_idx;
      }
      means = tmp_means;
    }
  }

  for (size_t i = 0; i < sinks_.size(); ++i) {
    sinks_[i].cluster_idx = solution[i];
  }

  fixSegmentLengths(means);
}

void Clustering::fixSegmentLengths(std::vector<std::pair<float, float>>& means)
{
  if (!branching_point_) {
    return;
  }
  // First, fix the middle positions
  const unsigned midIdx = means.size() / 2 - 1;

  fixSegment(branching_point_.value(), segment_length_ / 2.0, means[midIdx]);
  fixSegment(
      branching_point_.value(), segment_length_ / 2.0, means[midIdx + 1]);

  // Fix lower branch
  for (unsigned i = midIdx; i > 0; --i) {
    fixSegment(means[i], segment_length_, means[i - 1]);
  }

  // Fix upper branch
  for (size_t i = midIdx + 1; i < means.size() - 1; ++i) {
    fixSegment(means[i], segment_length_, means[i + 1]);
  }
}

void Clustering::fixSegment(const std::pair<float, float>& fixedPoint,
                            const float targetDist,
                            std::pair<float, float>& movablePoint)
{
  const float actualDist = calcDist(fixedPoint, movablePoint);
  if (actualDist == 0) {
    return;
  }
  const float ratio = targetDist / actualDist;

  const float dx = (movablePoint.first - fixedPoint.first) * ratio;
  const float dy = (movablePoint.second - fixedPoint.second) * ratio;

  movablePoint.first = fixedPoint.first + dx;
  movablePoint.second = fixedPoint.second + dy;
}

float Clustering::Kmeans(const unsigned n,
                         const unsigned cap,
                         const unsigned max,
                         const unsigned power,
                         std::vector<std::pair<float, float>>& means)
{
  // initialize matching indexes for sinks
  for (auto& sink : sinks_) {
    sink.cluster_idx = -1;
  }

  std::vector<std::vector<Sink*>> clusters;
  bool stop = false;
  // Kmeans optimization
  unsigned iter = 1;
  while (!stop) {
    fixSegmentLengths(means);

    // sink to cluster matching based on min-cost flow
    minCostFlow(means, cap, 5200, power);

    // collect results
    clusters.clear();
    clusters.resize(n);
    for (Sink& sink : sinks_) {
      int position = 0;
      if (sink.cluster_idx >= 0 && sink.cluster_idx < n) {
        position = sink.cluster_idx;
      } else {
        // Added to check wrong assignment

        float minimumDist;
        int minimumDistClusterIndex = -1;

        // Initialize minimumDist and minimumDistClusterIndex with a cluster
        // with size < cap
        for (size_t j = 0; j < means.size(); ++j) {
          if (clusters[j].size() < cap) {
            minimumDist = calcDist(
                std::make_pair(means[j].first, means[j].second), &sink);
            minimumDistClusterIndex = j;
            break;
          }
        }

        if (minimumDistClusterIndex == -1) {
          // No cluster with size < cap
          minimumDistClusterIndex = 0;
        } else {
          // Nearest Cluster with size < cap
          for (size_t j = 0; j < means.size(); ++j) {
            if (clusters[j].size() < cap) {
              const float currentDist = calcDist(
                  std::make_pair(means[j].first, means[j].second), &sink);
              if (currentDist < minimumDist) {
                minimumDist = currentDist;
                minimumDistClusterIndex = j;
              }
            }
          }
        }

        position = minimumDistClusterIndex;
      }
      clusters[position].push_back(&sink);
    }

    float delta = 0;

    // use weighted center
    for (unsigned i = 0; i < n; ++i) {
      float sum_x = 0, sum_y = 0;
      for (const auto& cluster : clusters[i]) {
        sum_x += cluster->x;
        sum_y += cluster->y;
      }
      const float pre_x = means[i].first;
      const float pre_y = means[i].second;

      if (!clusters[i].empty()) {
        means[i] = std::make_pair(sum_x / clusters[i].size(),
                                  sum_y / clusters[i].size());
        delta += std::abs(pre_x - means[i].first)
                 + std::abs(pre_y - means[i].second);
      }
    }

    clusters_ = clusters;

    if (iter > max || delta < 0.5) {
      stop = true;
    }

    ++iter;
  }

  return calcSilh(means);
}

float Clustering::calcSilh(
    const std::vector<std::pair<float, float>>& means) const
{
  // LEARN-CTS-02: exact Manhattan KD queries replace all-centroid scans.
  // A single centroid has no outside competitor: retain upstream behavior.
  if (ord::learning::enabled() && means.size() > 1 && !sinks_.empty()) {
    std::vector<ord::learning::Point> centroids;
    centroids.reserve(means.size());
    for (std::size_t i = 0; i < means.size(); ++i) {
      centroids.push_back({means[i].first, means[i].second, i});
    }
    const ord::learning::KdTree index(std::move(centroids));
    float sum = 0;
    for (const Sink& sink : sinks_) {
      if (sink.cluster_idx < 0 || static_cast<std::size_t>(sink.cluster_idx) >= means.size()) {
        continue;
      }
      const ord::learning::Point query{sink.x, sink.y, 0};
      const float inside = calcDist(means[sink.cluster_idx], &sink);
      const float outside = static_cast<float>(index.nearest(query, sink.cluster_idx).first);
      const float denominator = std::max(inside, outside);
      if (denominator != 0) {
        sum += (outside - inside) / denominator;
      }
    }
    return sum / sinks_.size();
  }
  float sum_silh = 0;
  for (const Sink& sink : sinks_) {
    float in_d = 0, out_d = FLT_MAX;
    for (size_t j = 0; j < means.size(); ++j) {
      const float x = means[j].first;
      const float y = means[j].second;
      if (sink.cluster_idx == j) {
        // within the cluster
        in_d = calcDist({x, y}, &sink);
      } else {
        // outside of the cluster
        const float d = calcDist({x, y}, &sink);
        out_d = std::min(d, out_d);
      }
    }
    const float temp = std::max(out_d, in_d);
    if (temp == 0) {
      if (out_d == 0) {
        sum_silh += -1;
      }
      if (in_d == 0) {
        sum_silh += 1;
      }
    } else {
      sum_silh += (out_d - in_d) / temp;
    }
  }
  return sum_silh / sinks_.size();
}

/*** Min-Cost Flow ********************************************************/
void Clustering::minCostFlow(const std::vector<std::pair<float, float>>& means,
                             const unsigned cap,
                             const float dist,
                             const unsigned power)
{
  // Builds src -> [sink nodes] -> [cluster nodes] - > target
  ListDigraph graph;

  // source and target
  ListDigraph::Node src = graph.addNode();
  ListDigraph::Node target = graph.addNode();

  // collection of nodes in the flow
  std::vector<ListDigraph::Node> sink_nodes, cluster_nodes;

  // add nodes / edges to graph
  // nodes for sinks
  for (size_t i = 0; i < sinks_.size(); ++i) {
    sink_nodes.push_back(graph.addNode());
  }
  // nodes for clusters
  for (size_t i = 0; i < means.size(); ++i) {
    cluster_nodes.push_back(graph.addNode());
  }

  // collection of edges in the flow
  std::vector<ListDigraph::Arc> src_sink_edges, sink_cluster_edges,
      cluster_sink_edges;

  // edges between source and sinks
  for (auto& sink : sink_nodes) {
    src_sink_edges.push_back(graph.addArc(src, sink));
  }
  // edges between sinks and clusters
  std::vector<double> costs;
  for (size_t i = 0; i < sinks_.size(); ++i) {
    for (size_t j = 0; j < means.size(); ++j) {
      double d = calcDist(means[j], &sinks_[i]);
      if (d <= dist) {
        d = std::pow(d, power);
        if (d < std::numeric_limits<int>::max()) {
          ListDigraph::Arc e = graph.addArc(sink_nodes[i], cluster_nodes[j]);
          sink_cluster_edges.push_back(e);
          costs.push_back(d);
        }
      }
    }
  }
  // edges between clusters and target
  for (auto& cluster : cluster_nodes) {
    cluster_sink_edges.push_back(graph.addArc(cluster, target));
  }

  debugPrint(logger_,
             CTS,
             "clustering",
             1,
             "Graph has {} nodes and {} edges",
             countNodes(graph),
             countArcs(graph));

  // formulate min-cost flow
  ListDigraph::ArcMap<int> edge_cost(graph), edge_capacity(graph);
  for (auto& edge : src_sink_edges) {
    edge_capacity[edge] = 1;
  }
  for (size_t i = 0; i < sink_cluster_edges.size(); ++i) {
    edge_capacity[sink_cluster_edges[i]] = 1;
    edge_cost[sink_cluster_edges[i]] = costs[i];
  }

  const int remaining = sinks_.size() % means.size();

  for (size_t i = 0; i < cluster_sink_edges.size(); ++i) {
    if (i < remaining) {
      edge_capacity[cluster_sink_edges[i]] = cap + 1;
    } else {
      edge_capacity[cluster_sink_edges[i]] = cap;
    }
  }

  for (ListDigraph::ArcIt it(graph); it != INVALID; ++it) {
    debugPrint(logger_,
               CTS,
               "clustering",
               2,
               "{}-{}",
               graph.id(graph.source(it)),
               graph.id(graph.target(it)));
    debugPrint(logger_, CTS, "clustering", 2, " cost = ", edge_cost[it]);
    debugPrint(logger_, CTS, "clustering", 2, " cap = ", edge_capacity[it]);
  }

  NetworkSimplex<ListDigraph, int, int> flow(graph);
  flow.costMap(edge_cost);
  flow.upperMap(edge_capacity);
  flow.stSupply(src, target, means.size() * cap + remaining);
  flow.run();
  ListDigraph::ArcMap<int> solution(graph);
  flow.flowMap(solution);

  ListDigraph::NodeMap<std::pair<int, int>> node_map(graph);
  for (size_t i = 0; i < sink_nodes.size(); ++i) {
    node_map[sink_nodes[i]] = {i, -1};
  }

  for (size_t i = 0; i < cluster_nodes.size(); ++i) {
    node_map[cluster_nodes[i]] = {-1, i};
  }

  node_map[src] = {-2, -2};
  node_map[target] = {-2, -2};

  for (ListDigraph::ArcIt it(graph); it != INVALID; ++it) {
    if (solution[it] == 0) {
      continue;
    }
    if (node_map[graph.source(it)].second == -1
        && node_map[graph.target(it)].first == -1) {
      debugPrint(logger_,
                 CTS,
                 "clustering",
                 3,
                 "Flow from: sink_{}  to cluster_{} flow = {}",
                 node_map[graph.source(it)].first,
                 node_map[graph.target(it)].second,
                 solution[it]);

      sinks_[node_map[graph.source(it)].first].cluster_idx
          = node_map[graph.target(it)].second;
    }
  }
}

void Clustering::getClusters(
    std::vector<std::vector<unsigned>>& newClusters) const
{
  newClusters.clear();
  newClusters.resize(clusters_.size());
  for (size_t i = 0; i < clusters_.size(); ++i) {
    newClusters[i].resize(clusters_[i].size());
    for (unsigned j = 0; j < clusters_[i].size(); ++j) {
      newClusters[i][j] = clusters_[i][j]->sink_idx;
    }
  }
}

/* static */
float Clustering::calcDist(const std::pair<float, float>& loc, const Sink* sink)
{
  return calcDist(loc, {sink->x, sink->y});
}

/* static */
float Clustering::calcDist(const std::pair<float, float>& loc1,
                           const std::pair<float, float>& loc2)
{
  return std::abs(loc1.first - loc2.first)
         + std::abs(loc1.second - loc2.second);
}

}  // namespace cts::CKMeans
