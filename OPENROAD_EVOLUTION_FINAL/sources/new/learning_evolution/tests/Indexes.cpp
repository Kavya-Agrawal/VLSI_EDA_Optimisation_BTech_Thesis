// SPDX-License-Identifier: BSD-3-Clause
#include "TestSupport.h"
#include "learning/Fenwick.h"
#include "learning/IntervalIndex.h"
#include "learning/LazyQueue.h"
#include "learning/SlackTree.h"
#include <algorithm>
#include <numeric>
#include <random>

namespace learning_test {
void testIndexes()
{
  using namespace ord::learning;
  std::mt19937 random(41);
  std::vector<double> values(37);
  Fenwick fenwick(values.size());
  SlackTree tree(values);
  for (unsigned iteration = 0; iteration < 1000; ++iteration) {
    const auto index = random() % values.size();
    const double replacement = double(int(random() % 201) - 100) / 10;
    fenwick.add(index, replacement - values[index]);
    values[index] = replacement;
    tree.update(index, replacement);
    const auto begin = random() % values.size();
    const auto end = begin + 1 + random() % (values.size() - begin);
    const double sum = std::accumulate(values.begin() + begin, values.begin() + end, 0.0);
    CHECK(near(fenwick.range(begin, end), sum));
    const auto summary = tree.query(begin, end);
    CHECK(near(summary.worst, *std::min_element(values.begin() + begin, values.begin() + end)));
    double tns = 0;
    for (auto i = begin; i < end; ++i) {
      tns += std::min(0.0, values[i]);
    }
    CHECK(near(summary.negative_sum, tns));
    CHECK(summary.count == end - begin);
  }
  CHECK(tree.query(3, 3).count == 0);
  rejects([&] { tree.update(37, 1); });
  rejects([&] { tree.query(5, 4); });
  rejects([&] { fenwick.prefix(38); });
  Fenwick selection(4);
  selection.add(0, 2);
  selection.add(1, 3);
  selection.add(3, 5);
  CHECK(selection.select(1) == 0);
  CHECK(selection.select(2) == 0);
  CHECK(selection.select(3) == 1);
  CHECK(selection.select(6) == 3);
  CHECK(selection.select(11) == 4);
  std::vector<Interval> intervals;
  for (unsigned i = 0; i < 100; ++i) {
    const double begin = random() % 100;
    intervals.push_back({begin, begin + random() % 20, i});
  }
  IntervalIndex interval_index(intervals);
  for (unsigned i = 0; i < 100; ++i) {
    const double begin = random() % 100;
    const double end = begin + random() % 20;
    std::vector<std::size_t> expected;
    for (const auto& interval : intervals) {
      if (interval.begin <= end && interval.end >= begin) {
        expected.push_back(interval.id);
      }
    }
    CHECK(interval_index.overlaps(begin, end) == expected);
  }
  CHECK(IntervalIndex({}).overlaps(0, 1).empty());
  rejects([] { IntervalIndex({{2, 1, 0}}); });
  LazyQueue queue;
  queue.update(1, 10);
  queue.update(1, 2);
  queue.update(2, 5);
  CHECK(queue.pop()->first == 2);
  CHECK(queue.pop()->first == 1);
  CHECK(!queue.pop());
  queue.update(3, 100);
  queue.erase(3);
  queue.update(3, 1);
  CHECK(near(queue.pop()->second, 1));
  CHECK(!queue.pop());
  queue.update(7, 2);
  queue.update(6, 2);
  CHECK(queue.pop()->first == 6);
  CHECK(queue.pop()->first == 7);
}
}  // namespace learning_test
