// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2019-2025, The OpenROAD Authors

#include "SinkClustering.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

#include "CtsObserver.h"
#include "CtsOptions.h"
#include "HTreeBuilder.h"
#include "TechChar.h"
#include "TreeBuilder.h"
#include "Util.h"
#include "stt/SteinerTreeBuilder.h"
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

// BEGIN INTEGRATED KERNEL DisjointSet
// SPDX-License-Identifier: BSD-3-Clause
#include <cstddef>
#include <numeric>
#include <stdexcept>
#include <utility>
#include <vector>

namespace ord::learning {
class DisjointSet
{
 public:
  explicit DisjointSet(std::size_t size) : parent_(size), sizes_(size, 1), components_(size)
  {
    std::iota(parent_.begin(), parent_.end(), 0);
  }

  std::size_t find(std::size_t node)
  {
    if (node >= parent_.size()) {
      throw std::out_of_range("DisjointSet node");
    }
    while (parent_[node] != node) {
      parent_[node] = parent_[parent_[node]];
      node = parent_[node];
    }
    return node;
  }

  bool unite(std::size_t a, std::size_t b)
  {
    a = find(a);
    b = find(b);
    if (a == b) {
      return false;
    }
    if (sizes_[a] < sizes_[b]) {
      std::swap(a, b);
    }
    parent_[b] = a;
    sizes_[a] += sizes_[b];
    --components_;
    return true;
  }

  std::size_t componentSize(std::size_t node) { return sizes_[find(node)]; }
  std::size_t components() const { return components_; }

 private:
  std::vector<std::size_t> parent_;
  std::vector<std::size_t> sizes_;
  std::size_t components_;
};
}  // namespace ord::learning
// END INTEGRATED KERNEL DisjointSet

// BEGIN INTEGRATED KERNEL SpanningTree
// SPDX-License-Identifier: BSD-3-Clause
#include <tuple>

namespace ord::learning {
struct SpatialEdge
{
  std::size_t from;
  std::size_t to;
  double weight;
};

inline std::vector<SpatialEdge> kruskal(std::size_t vertices,
                                       std::vector<SpatialEdge> edges)
{
  for (const auto& edge : edges) {
    if (edge.from >= vertices || edge.to >= vertices || !std::isfinite(edge.weight)) {
      throw std::invalid_argument("Invalid spanning-tree edge");
    }
  }
  std::sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {
    return std::tie(a.weight, a.from, a.to) < std::tie(b.weight, b.from, b.to);
  });
  DisjointSet sets(vertices);
  std::vector<SpatialEdge> tree;
  for (const auto& edge : edges) {
    if (sets.unite(edge.from, edge.to)) {
      tree.push_back(edge);
    }
  }
  return tree;  // A forest if the input graph is disconnected.
}

inline std::vector<SpatialEdge> denseManhattanTree(const std::vector<Point>& points)
{
  std::vector<SpatialEdge> edges;
  for (std::size_t i = 0; i < points.size(); ++i) {
    for (std::size_t j = i + 1; j < points.size(); ++j) {
      edges.push_back({i, j, manhattan(points[i], points[j])});
    }
  }
  return kruskal(points.size(), std::move(edges));
}

// Double-tree preorder gives a <=2 metric tour, prior to optional local search.
inline std::vector<std::size_t> preorderTour(std::size_t vertices,
                                            const std::vector<SpatialEdge>& tree)
{
  if (!vertices) {
    return {};
  }
  std::vector<std::vector<std::size_t>> adjacent(vertices);
  for (const auto& edge : tree) {
    adjacent.at(edge.from).push_back(edge.to);
    adjacent.at(edge.to).push_back(edge.from);
  }
  std::vector<bool> seen(vertices, false);
  std::vector<std::size_t> order;
  std::vector<std::size_t> pending{0};
  while (!pending.empty()) {
    const auto node = pending.back();
    pending.pop_back();
    if (seen[node]) {
      continue;
    }
    seen[node] = true;
    order.push_back(node);
    auto& next = adjacent[node];
    std::sort(next.rbegin(), next.rend());
    pending.insert(pending.end(), next.begin(), next.end());
  }
  if (order.size() != vertices) {
    throw std::invalid_argument("Tour needs a connected tree");
  }
  return order;
}
}  // namespace ord::learning
// END INTEGRATED KERNEL SpanningTree

// BEGIN INTEGRATED KERNEL LocalSearch
// SPDX-License-Identifier: BSD-3-Clause
#include <numeric>

namespace ord::learning {
inline double tourLength(const std::vector<Point>& points,
                         const std::vector<std::size_t>& tour)
{
  if (tour.size() < 2) {
    return 0;
  }
  double total = 0;
  for (std::size_t i = 0; i < tour.size(); ++i) {
    total += manhattan(points.at(tour[i]), points.at(tour[(i + 1) % tour.size()]));
  }
  return total;
}

inline std::vector<std::size_t> twoOpt(const std::vector<Point>& points,
                                      std::vector<std::size_t> tour,
                                      unsigned max_passes)
{
  for (unsigned pass = 0; pass < max_passes; ++pass) {
    bool improved = false;
    for (std::size_t i = 0; i + 2 < tour.size(); ++i) {
      for (std::size_t j = i + 2; j < tour.size(); ++j) {
        const auto next = (j + 1) % tour.size();
        const double before = manhattan(points.at(tour[i]), points.at(tour[i + 1]))
                              + manhattan(points.at(tour[j]), points.at(tour[next]));
        const double after = manhattan(points.at(tour[i]), points.at(tour[j]))
                             + manhattan(points.at(tour[i + 1]), points.at(tour[next]));
        if (after + 1e-12 < before) {
          std::reverse(tour.begin() + i + 1, tour.begin() + j + 1);
          improved = true;
        }
      }
    }
    if (!improved) {
      break;
    }
  }
  return tour;
}

inline std::vector<std::size_t> farthestFirst(const std::vector<Point>& points,
                                              std::size_t count)
{
  if (points.empty() || count == 0) {
    return {};
  }
  count = std::min(count, points.size());
  std::vector<std::size_t> centers{0};
  std::vector<bool> chosen(points.size(), false);
  chosen[0] = true;
  std::vector<double> distances(points.size(), std::numeric_limits<double>::infinity());
  while (centers.size() < count) {
    for (std::size_t i = 0; i < points.size(); ++i) {
      distances[i] = std::min(distances[i], manhattan(points[i], points[centers.back()]));
    }
    std::size_t best = 0;
    double farthest = -1;
    for (std::size_t i = 0; i < points.size(); ++i) {
      if (!chosen[i] && distances[i] > farthest) {
        best = i;
        farthest = distances[i];
      }
    }
    chosen[best] = true;
    centers.push_back(best);
  }
  return centers;
}
}  // namespace ord::learning
// END INTEGRATED KERNEL LocalSearch

// BEGIN INTEGRATED KERNEL SpatialOrder
// SPDX-License-Identifier: BSD-3-Clause
#include <numeric>

namespace ord::learning {
inline std::vector<std::size_t> spatialOrder(const std::vector<Point>& points,
                                            PolicyConfig config = policyConfig())
{
  std::vector<std::size_t> order(points.size());
  std::iota(order.begin(), order.end(), 0);
  if (points.size() < 2) {
    return order;
  }
  Bounds bounds;
  for (const auto& point : points) {
    if (!std::isfinite(point.x) || !std::isfinite(point.y)) {
      throw std::invalid_argument("Spatial ordering needs finite coordinates");
    }
    bounds.extend(point);
  }
  if (config.spatial_mode == 0) {
    return order;
  }
  if (config.spatial_mode == 2 && points.size() <= 512) {
    // Dense MST is deliberately capped to bound quadratic memory.
    return twoOpt(points, preorderTour(points.size(), denseManhattanTree(points)), 2);
  }
  const KdTree index(points);
  std::vector<std::uint64_t> keys;
  std::vector<double> isolation;
  for (const auto& point : points) {
    keys.push_back(mortonKey(point, bounds));
    isolation.push_back(index.nearest(point, point.id).first);
  }
  std::stable_sort(order.begin(), order.end(), [&](auto a, auto b) {
    if (keys[a] != keys[b]) {
      return keys[a] < keys[b];
    }
    if (isolation[a] != isolation[b]) {
      return isolation[a] < isolation[b];
    }
    return a < b;
  });
  return order;
}
}  // namespace ord::learning
// END INTEGRATED KERNEL SpatialOrder

namespace cts {

using std::vector;
using utl::CTS;

SinkClustering::SinkClustering(const CtsOptions* options,
                               TechChar* techChar,
                               HTreeBuilder* HTree)
    : options_(options),
      logger_(options->getLogger()),
      techChar_(techChar),
      maxInternalDiameter_(10),
      capPerUnit_(0.0),
      use_max_diameter_((HTree->getTreeType() == TreeType::MacroTree)
                            ? options->isMacroMaxDiameterSet()
                            : options->isMaxDiameterSet()),
      use_max_size_((HTree->getTreeType() == TreeType::MacroTree)
                        ? options->isMacroSinkClusteringSizeSet()
                        : options->isSinkClusteringSizeSet()),
      useMaxCapLimit_(!(use_max_size_ && use_max_diameter_)),
      scaleFactor_(1),
      HTree_(HTree)
{
}

void SinkClustering::normalizePoints(float maxDiameter)
{
  if (firstRun_) {
    double xMax = -std::numeric_limits<double>::infinity();
    double xMin = std::numeric_limits<double>::infinity();
    double yMax = -std::numeric_limits<double>::infinity();
    double yMin = std::numeric_limits<double>::infinity();
    for (const Point<double>& p : points_) {
      xMax = std::max(p.getX(), xMax);
      yMax = std::max(p.getY(), yMax);
      xMin = std::min(p.getX(), xMin);
      yMin = std::min(p.getY(), yMin);
    }

    const double xSpan = xMax - xMin;
    const double ySpan = yMax - yMin;
    xSpan_ = xSpan;
    ySpan_ = ySpan;
    for (Point<double>& p : points_) {
      const double x = p.getX();
      const double xNorm = xSpan ? (x - xMin) / xSpan : 0;
      const double y = p.getY();
      const double yNorm = ySpan ? (y - yMin) / ySpan : 0;
      p = Point<double>(xNorm, yNorm);
    }
  }
  double span;
  if (xSpan_ == 0 && ySpan_ == 0) {
    span = 1;  // arbitrary
  } else if (xSpan_ == 0) {
    span = ySpan_;
  } else if (ySpan_ == 0) {
    span = xSpan_;
  } else {
    span = std::min(xSpan_, ySpan_);
  }
  maxInternalDiameter_ = maxDiameter / span;
  capPerUnit_ = techChar_->getCapPerDBU() * scaleFactor_ * span;

  // clang-format off
  debugPrint(logger_, CTS, "clustering", 1, "normalizePoints: "
             "maxInternalDiameter_:{} xSpan:{} ySpan:{}",
             maxInternalDiameter_, xSpan_, ySpan_);
  // clang-format on
}

void SinkClustering::computeAllThetas()
{
  if (firstRun_) {
    for (unsigned idx = 0; idx < points_.size(); ++idx) {
      const Point<double>& p = points_[idx];
      const double theta = computeTheta(p.getX(), p.getY());
      thetaIndexVector_.emplace_back(theta, idx);
    }
    // clang-format off
    debugPrint(logger_, CTS, "clustering", 1, "SinkClustering::computeAllThetas:"
               " thetaIndexVector_ has {} elems", thetaIndexVector_.size());
    // clang-format on
  }
}

void SinkClustering::sortPoints()
{
  if (firstRun_) {
    // LEARN-CTS-01: opt-in spatial scheduling replaces angular sorting.
    // The original algorithm remains available in SinkClustering_old.cpp.
    if (ord::learning::enabled()) {
      std::vector<ord::learning::Point> spatial_points;
      spatial_points.reserve(points_.size());
      for (std::size_t i = 0; i < points_.size(); ++i) {
        spatial_points.push_back({points_[i].getX(), points_[i].getY(), i});
      }
      const auto order = ord::learning::spatialOrder(spatial_points);
      thetaIndexVector_.clear();
      thetaIndexVector_.reserve(order.size());
      for (std::size_t rank = 0; rank < order.size(); ++rank) {
        // Monotone synthetic theta preserves downstream angular indexing.
        const double theta = order.empty() ? 0.0 : double(rank) / order.size();
        thetaIndexVector_.emplace_back(theta, order[rank]);
      }
    } else {
      std::ranges::sort(thetaIndexVector_);
    }
  }
}

/* static */
bool SinkClustering::isOne(const double pos)
{
  return (1 - pos) < std::numeric_limits<double>::epsilon();
}

/* static */
bool SinkClustering::isZero(const double pos)
{
  return pos < std::numeric_limits<double>::epsilon();
}

double SinkClustering::computeTheta(const double x, const double y) const
{
  if (isOne(x) && isOne(y)) {
    return 0.5;
  }

  const unsigned quad = numVertex(std::min(unsigned(2.0 * x), (unsigned) 1),
                                  std::min(unsigned(2.0 * y), (unsigned) 1));

  double t = computeTheta(2 * std::fabs(x - 0.5), 2 * std::fabs(y - 0.5));

  if (quad % 2 == 1) {
    t = 1 - t;
  }

  double integral;
  const double fractal = std::modf((quad + t) / 4.0 + 7.0 / 8.0, &integral);
  return fractal;
}

unsigned SinkClustering::numVertex(const unsigned x, const unsigned y) const
{
  if ((x == 0) && (y == 0)) {
    return 0;
  }
  if ((x == 0) && (y == 1)) {
    return 1;
  }
  if ((x == 1) && (y == 1)) {
    return 2;
  }
  if ((x == 1) && (y == 0)) {
    return 3;
  }

  logger_->error(CTS, 58, "Invalid parameters in {}.", __func__);

  // avoid warn message
  return 4;
}

void SinkClustering::run(const unsigned groupSize,
                         const float maxDiameter,
                         const int scaleFactor,
                         unsigned& bestSize,
                         float& bestDiameter)
{
  scaleFactor_ = scaleFactor;

  // clang-format off
  debugPrint(logger_, CTS, "clustering", 1, "SinkClustering::run points_ "
             "has {} elems", points_.size());
  // clang-format on
  if (firstRun_) {
    const auto& original_points = points_;
    if (CtsObserver* observer = options_->getObserver()) {
      observer->initializeWithPoints(this, original_points);
    }
  }
  normalizePoints(maxDiameter);
  computeAllThetas();
  sortPoints();
  bool bestSolutionFound = findBestMatching(groupSize);
  if (logger_->debugCheck(CTS, "Stree", 1)) {
    writePlotFile(groupSize);
  }

  firstRun_ = false;
  if (bestSolutionFound) {
    bestSize = groupSize;
    bestDiameter = maxDiameter;
  }
}

void SinkClustering::repairClusteringSolution(
    const unsigned groupSize,
    vector<vector<Point<double>>>& solutionPoints,
    vector<vector<unsigned>>& solutionPointsIdx,
    vector<vector<unsigned>>& solutions,
    int& single_cluster_count,
    int& solved_cluster_count)
{
  int cluster_num = solutions.size();
  for (int c = 0; c < cluster_num; ++c) {
    // only clusters with a single sink
    if (solutionPoints[c].size() == 1) {
      single_cluster_count++;
      // get info of the single sink
      const unsigned idx = solutionPointsIdx[c][0];
      const Point<double>& p = points_[idx];
      // init variables to repair
      double min_dist_to_add = maxInternalDiameter_;
      int min_sink_idx_to_add = -1, min_cluster_idx_to_add = -1;
      double min_dist_to_merge = maxInternalDiameter_;
      int cluster_idx_to_merge = -1;
      // Find cluster to add one sink
      for (int k = 0; k < cluster_num; ++k) {
        if (k == c) {
          continue;
        }
        // iter all sinks of candidate cluster
        unsigned pointIdx = 0;
        double distanceCost = 0;
        double capCost = pointsCap_[idx];
        for (const auto& comparisonPoint : solutionPoints[k]) {
          const double cost = HTree_->computeDist(p, comparisonPoint);
          const double cap_cost
              = pointsCap_[idx]
                + (cost * capPerUnit_
                   + pointsCap_[solutionPointsIdx[k][pointIdx]]);
          if (solutionPoints[k].size() > 2 && cost < min_dist_to_add
              && !isLimitExceeded(2, cost, cap_cost, groupSize)) {
            min_dist_to_add = cost;
            min_sink_idx_to_add = pointIdx;
            min_cluster_idx_to_add = k;
          }
          if (useMaxCapLimit_) {
            capCost += cost * capPerUnit_
                       + pointsCap_[solutionPointsIdx[k][pointIdx]];
          }
          pointIdx++;
          distanceCost = std::max(cost, distanceCost);
        }

        if (!isLimitExceeded(
                solutionPoints[k].size(), distanceCost, capCost, groupSize)
            && distanceCost < min_dist_to_merge) {
          cluster_idx_to_merge = k;
          min_dist_to_merge = distanceCost;
        }
      }
      // cluster found to merge the single cluster
      if (cluster_idx_to_merge != -1) {
        solved_cluster_count++;
        // Add sink to found cluster
        solutionPoints[cluster_idx_to_merge].push_back(p);
        solutionPointsIdx[cluster_idx_to_merge].push_back(idx);
        solutions[cluster_idx_to_merge].push_back(idx);
        // move cluster to the last to remove it from the vectors
        std::swap(solutionPoints[c], solutionPoints[cluster_num - 1]);
        solutionPoints.pop_back();
        std::swap(solutionPointsIdx[c], solutionPointsIdx[cluster_num - 1]);
        solutionPointsIdx.pop_back();
        std::swap(solutions[c], solutions[cluster_num - 1]);
        solutions.pop_back();
        cluster_num--;
        if (c < cluster_num && solutionPoints[c].size() == 1) {
          c--;
        }
      }
      // if it can not be added on cluster near and there is a sink near, then
      // add the sink on cluster
      else if (min_cluster_idx_to_add != -1) {
        solved_cluster_count++;
        // add the more nearby sink on cluster
        const unsigned idx_p
            = solutionPointsIdx[min_cluster_idx_to_add][min_sink_idx_to_add];
        solutionPoints[c].push_back(points_[idx_p]);
        solutionPointsIdx[c].push_back(idx_p);
        solutions[c].push_back(idx_p);
        // delete the sink of old cluster
        const unsigned old_size = solutionPoints[min_cluster_idx_to_add].size();
        std::swap(solutionPoints[min_cluster_idx_to_add][min_sink_idx_to_add],
                  solutionPoints[min_cluster_idx_to_add][old_size - 1]);
        solutionPoints[min_cluster_idx_to_add].pop_back();
        std::swap(
            solutionPointsIdx[min_cluster_idx_to_add][min_sink_idx_to_add],
            solutionPointsIdx[min_cluster_idx_to_add][old_size - 1]);
        solutionPointsIdx[min_cluster_idx_to_add].pop_back();
        std::swap(solutions[min_cluster_idx_to_add][min_sink_idx_to_add],
                  solutions[min_cluster_idx_to_add][old_size - 1]);
        solutions[min_cluster_idx_to_add].pop_back();
      }
    }
  }
}

bool SinkClustering::findBestMatching(const unsigned groupSize)
{
  // Counts how many clusters are in each solution.
  vector<unsigned> clusters(groupSize, 0);
  // Keeps track of the total cost of each solution.
  vector<double> costs(groupSize, 0);
  vector<double> previousCosts(groupSize, 0);
  // Has the max diameter of each solution.
  vector<double> max_diameter(groupSize, 0);
  // Has the max size of each solution.
  vector<unsigned> max_size(groupSize, 0);
  // Has the points for each cluster of each solution.
  vector<vector<vector<Point<double>>>> solutionPoints(groupSize);
  // Has the points index for each cluster of each solution.
  // example: solutionsPointsIdx[solutionId][clusterIdx][pointIdx]
  vector<vector<vector<unsigned>>> solutionPointsIdx(groupSize);
  // Has the sink indexes for each cluster of each solution.
  vector<vector<vector<unsigned>>> solutions(groupSize);

  if (useMaxCapLimit_) {
    debugPrint(logger_,
               CTS,
               "Stree",
               1,
               "Clustering with max cap limit of {:.3e}",
               options_->getSinkBufferInputCap() * kMaxCapFactor);
  }
  const unsigned sinks_num = thetaIndexVector_.size();
  if (sinks_num == 0) {
    return false;
  }
  for (unsigned j = 0; j < groupSize; ++j) {
    for (unsigned i = 0; i < sinks_num; ++i) {
      if (solutions[j].empty()) {
        // Create first cluster on vector
        solutions[j].emplace_back();
        solutionPoints[j].emplace_back();
        solutionPointsIdx[j].emplace_back();
      }
      // Get the current point
      const unsigned idx = thetaIndexVector_[(i + j) % sinks_num].second;
      const Point<double>& p = points_[idx];
      double distanceCost = 0;
      double capCost = pointsCap_[idx];
      unsigned pointIdx = 0;
      // Check the distance from the current point to others in the cluster,
      // if there are any.
      for (const auto& comparisonPoint : solutionPoints[j][clusters[j]]) {
        const double cost = HTree_->computeDist(p, comparisonPoint);
        if (useMaxCapLimit_) {
          capCost += cost * capPerUnit_
                     + pointsCap_[solutionPointsIdx[j][clusters[j]][pointIdx]];
        }
        pointIdx++;
        distanceCost = std::max(cost, distanceCost);
      }
      // If the cluster size is higher than groupSize,
      // or the distance is higher than maxInternalDiameter_
      //-> start another cluster and save the cost of the current one.
      if (isLimitExceeded(solutionPoints[j][clusters[j]].size(),
                          distanceCost,
                          capCost,
                          groupSize)) {
        debugPrint(logger_,
                   CTS,
                   "Stree",
                   4,
                   "Created cluster of size {}, dia {:.3}, cap {:.3e}",
                   solutionPoints[j][clusters[j]].size(),
                   distanceCost,
                   capCost);
        max_diameter[j] = std::max(max_diameter[j], previousCosts[j]);
        max_size[j] = std::max(
            max_size[j], (unsigned) solutionPoints[j][clusters[j]].size());
        // The cost is computed as the highest cost found on the current
        // cluster
        if (previousCosts[j] == 0) {
          previousCosts[j] = maxInternalDiameter_;
        }
        costs[j] += previousCosts[j];
        // A new cluster is defined
        clusters[j] = clusters[j] + 1;
        // The cost was already saved, so the same structure can be used for
        // the next cluster.
        previousCosts[j] = 0;
      } else {
        // Node will be a part of the current cluster, thus, save the highest
        // cost.
        previousCosts[j] = std::max(distanceCost, previousCosts[j]);
      }
      // Add vectors in case they are no allocated yet. (Depends if a new
      // cluster was defined above)
      if (solutions[j].size() < (clusters[j] + 1)) {
        solutions[j].emplace_back();
        solutionPoints[j].emplace_back();
        solutionPointsIdx[j].emplace_back();
      }
      // Save the current Point in it's respective cluster. (Depends if a new
      // cluster was defined above)
      solutionPoints[j][clusters[j]].push_back(p);
      solutionPointsIdx[j][clusters[j]].push_back(idx);
      solutions[j][clusters[j]].push_back(idx);
    }
  }

  unsigned bestSolution = 0;
  bool bestSolutionFound = false;

  // Find the solution with minimum cost.
  for (unsigned j = 1; j < groupSize; ++j) {
    if (logger_->debugCheck(CTS, "clustering", 1)) {
      // clang-format off
      logger_->report("Solution from group has {:0.3f} cost and {}"
                      " clustered sinks", j, costs[j], solutions[j].size());
      // clang-format on
    }
    if (costs[j] < bestSolutionCost_) {
      bestSolution = j;
      bestSolutionCost_ = costs[j];
      bestSolutionFound = true;
    }
  }
  debugPrint(logger_,
             CTS,
             "Stree",
             2,
             "Best solution cost = {:.3}",
             bestSolutionCost_);
  // Save the solution for the Tree Builder.
  if (bestSolutionFound) {
    // Repair single sink on cluster
    int single_cluster_count = 0;
    int solved_cluster_count = 0;
    repairClusteringSolution(groupSize,
                             solutionPoints[bestSolution],
                             solutionPointsIdx[bestSolution],
                             solutions[bestSolution],
                             single_cluster_count,
                             solved_cluster_count);
    if (logger_->debugCheck(CTS, "clustering", 2)) {
      logger_->report(
          "Best solution has {} clusters with single sink, {} clusters move to "
          "nearby cluster",
          single_cluster_count,
          solved_cluster_count);
    }
    bestSolution_ = solutions[bestSolution];
    // Calculate max diameter to save
    double span;
    if (xSpan_ == 0 && ySpan_ == 0) {
      span = 1;  // arbitrary
    } else if (xSpan_ == 0) {
      span = ySpan_;
    } else if (ySpan_ == 0) {
      span = xSpan_;
    } else {
      span = std::min(xSpan_, ySpan_);
    }
    max_diameter_ = max_diameter[bestSolution] * span;
    max_size_ = max_size[bestSolution];
    // clang-format off
    debugPrint(logger_, CTS, "clustering", 1, "Best solution from group "
               "{} has cost of {:0.3f} and size of {}", bestSolution,
               bestSolutionCost_, bestSolution_.size());
    // clang-format on
  }
  if (logger_->debugCheck(CTS, "clustering", 2)) {
    size_t solnIndex = 0;
    for (const std::vector<unsigned>& soln : bestSolution_) {
      std::ostringstream s;
      s << "Solution " << solnIndex << "[" << soln.size() << "]: ";
      for (const unsigned i : soln) {
        s << i << " ";
      }
      logger_->debug(CTS, "clustering", "{}", s.str());
      ++solnIndex;
    }
  }

  return bestSolutionFound;
}

bool SinkClustering::isLimitExceeded(const unsigned size,
                                     const double cost,
                                     const double capCost,
                                     const unsigned sizeLimit)
{
  return (useMaxCapLimit_
          && (capCost > options_->getSinkBufferInputCap() * kMaxCapFactor))
         || (use_max_size_ && (size >= sizeLimit))
         || (use_max_diameter_ && (cost > maxInternalDiameter_));
}

void SinkClustering::writePlotFile(unsigned groupSize)
{
  std::ofstream file("plot_clustering.py");
  file << "import numpy as np\n";
  file << "import matplotlib.pyplot as plt\n";
  file << "import matplotlib.path as mpath\n";
  file << "import matplotlib.lines as mlines\n";
  file << "import matplotlib.patches as mpatches\n";
  file << "from matplotlib.collections import PatchCollection\n\n";
  const vector<const char*> colors{"tab:blue",
                                   "tab:orange",
                                   "tab:green",
                                   "tab:red",
                                   "tab:purple",
                                   "tab:brown",
                                   "tab:pink",
                                   "tab:gray",
                                   "tab:olive",
                                   "tab:cyan"};
  const vector<char> markers{'*', 'o', 'x', '+', 'v', '^', '<', '>'};

  unsigned clusterCounter = 0;
  double totalWL = 0;
  for (const vector<unsigned>& clusters : bestSolution_) {
    const unsigned color = clusterCounter % colors.size();
    const unsigned marker = (clusterCounter / colors.size()) % markers.size();
    vector<Point<double>> clusterNodes;
    for (unsigned idx : clusters) {
      const Point<double>& point = points_[idx];
      clusterNodes.emplace_back(points_[idx]);
      file << "plt.scatter(" << point.getX() << ", " << point.getY() << ", c=\""
           << colors[color] << "\", marker='" << markers[marker] << "')\n";
    }
    const double wl = getWireLength(clusterNodes);
    totalWL += wl;
    clusterCounter++;
  }
  logger_->report(
      "Total cluster WL = {:.3} for {} clusters.", totalWL, clusterCounter);
  file << "plt.show()\n";
  file.close();
}

double SinkClustering::getWireLength(const vector<Point<double>>& points) const
{
  vector<int> vecX;
  vector<int> vecY;
  double driverX = 0;
  double driverY = 0;
  for (const auto& point : points) {
    driverX += point.getX();
    driverY += point.getY();
  }
  driverX /= points.size();
  driverY /= points.size();
  vecX.emplace_back(driverX * options_->getDbUnits());
  vecY.emplace_back(driverY * options_->getDbUnits());

  for (const auto& point : points) {
    vecX.emplace_back(point.getX() * options_->getDbUnits());
    vecY.emplace_back(point.getY() * options_->getDbUnits());
  }
  stt::SteinerTreeBuilder* sttBuilder = options_->getSttBuilder();
  const stt::Tree pdTree = sttBuilder->makeSteinerTree(vecX, vecY, 0);
  const int wl = pdTree.length;
  return wl / double(options_->getDbUnits());
}

}  // namespace cts
