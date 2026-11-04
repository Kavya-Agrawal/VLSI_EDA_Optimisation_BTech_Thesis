// SPDX-License-Identifier: BSD-3-Clause
#include "TestSupport.h"
#include "learning/BudgetDp.h"
#include "learning/RollbackSet.h"
#include "learning/SlackTree.h"
#include "learning/TimingDag.h"
#include <chrono>
#include <fstream>
#include <iomanip>

namespace learning_test {
void testModel()
{
  using namespace ord::learning;
  RollbackSet sets(8);
  const auto original = sets.checkpoint();
  sets.unite(0, 1);
  const auto first = sets.checkpoint();
  sets.unite(1, 2);
  sets.unite(2, 3);
  CHECK(sets.componentSize(0) == 4);
  sets.rollback(first);
  CHECK(sets.componentSize(0) == 2);
  CHECK(sets.find(2) != sets.find(0));
  sets.unite(4, 5);
  sets.unite(0, 4);
  CHECK(sets.componentSize(0) == 4);
  sets.rollback(original);
  for (unsigned i = 0; i < 8; ++i) {
    CHECK(sets.find(i) == i);
  }
  rejects([&] { sets.rollback(10); });
  // A model-level ablation: re-evaluate selected repairs through graph timing.
  // Unlike the slide scenario, these values come from executable arithmetic.
  const std::vector<BudgetItem> items{
    {0, 3, .10}, {1, 3, .10}, {2, 4, .13},
    {3, 5, .60}, {4, 5, .60}, {5, 6, .90}};
  std::vector<double> delays(40);
  for (std::size_t i = 0; i < delays.size(); ++i) {
    delays[i] = i % 2 ? 6 : 5;
  }
  const auto measure = [&](const std::vector<std::size_t>& selection) {
    TimingDag graph(delays);
    for (std::size_t i = 0; i < delays.size(); i += 2) {
      graph.addEdge(i, i + 1);
    }
    for (auto id : selection) {
      graph.setDelay(id * 2 + 1, 6 - items[id].benefit);
    }
    graph.compile();
    const auto slack = graph.slacks(10);
    std::vector<double> endpoints;
    for (std::size_t i = 1; i < slack.size(); i += 2) {
      endpoints.push_back(slack[i]);
    }
    return SlackTree(endpoints).query(0, endpoints.size());
  };
  const auto baseline = measure({0, 1, 2});
  const auto greedy = measure(budgetGreedy(items, 10).ids);
  const auto evolved = measure(budgetDp(items, 10).ids);
  CHECK(near(baseline.negative_sum, -19.67));
  CHECK(near(greedy.negative_sum, -19.00));
  CHECK(near(evolved.negative_sum, -18.80));
  CHECK(evolved.worst == -1);
  const double gain = 100 * (evolved.negative_sum - baseline.negative_sum)
                      / std::abs(baseline.negative_sum);
  CHECK(gain > 4.4 && gain < 4.5);
  std::cout << std::fixed << std::setprecision(4)
            << "Measured synthetic circuit: first-fit TNS " << baseline.negative_sum
            << ", greedy " << greedy.negative_sum
            << ", DP " << evolved.negative_sum
            << "; DP gain " << gain << "% (not OpenROAD QoR)\n";
}
}  // namespace learning_test
