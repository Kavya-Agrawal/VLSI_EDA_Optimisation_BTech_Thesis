// SPDX-License-Identifier: BSD-3-Clause
#include "TestSupport.h"
#include "learning/BudgetDp.h"
#include "learning/Pareto.h"
#include "learning/PartitionDp.h"
#include <random>
#include <set>

namespace learning_test {
void testOptimization()
{
  using namespace ord::learning;
  std::mt19937 random(103);
  for (unsigned trial = 0; trial < 200; ++trial) {
    std::vector<BudgetItem> items;
    for (unsigned i = 0; i < 9; ++i) {
      items.push_back({i, 1u + static_cast<unsigned>(random() % 8), double(random() % 100) / 10});
    }
    const unsigned budget = random() % 21;
    double oracle = 0;
    for (unsigned mask = 0; mask < (1u << items.size()); ++mask) {
      unsigned cost = 0;
      double benefit = 0;
      for (std::size_t i = 0; i < items.size(); ++i) {
        if (mask & (1u << i)) {
          cost += items[i].cost;
          benefit += items[i].benefit;
        }
      }
      if (cost <= budget) {
        oracle = std::max(oracle, benefit);
      }
    }
    const auto selection = budgetDp(items, budget);
    CHECK(near(selection.benefit, oracle));
    CHECK(selection.cost <= budget);
    CHECK(std::set<std::size_t>(selection.ids.begin(), selection.ids.end()).size() == selection.ids.size());
    CHECK(budgetGreedy(items, budget).benefit <= oracle + 1e-9);
  }
  rejects([] { budgetDp({{0, 0, 1}}, 1); });
  CHECK(budgetDp({}, 0).ids.empty());
  const auto partition = partitionDp({1, 1, 2, 2}, 2, 3);
  CHECK(near(partition.cost, 20));
  CHECK(partition.groups.size() == 2);
  CHECK(partition.groups.front().first == 0);
  CHECK(partition.groups.back().second == 4);
  rejects([] { partitionDp({1, 2, 3}, 1, 2); });
  rejects([] { partitionDp({-1, 2}, 2, 1); });
  const std::vector<Objective> objectives{
    {0, {1, 1, 1}}, {1, {2, 2, 2}}, {2, {0, 3, 1}}, {3, {3, 3, 3}}};
  const auto front = paretoFront(objectives);
  CHECK(front.size() == 2);
  CHECK(front[0].id == 0);
  CHECK(front[1].id == 2);
  const auto layers = nondominatedLayers(objectives);
  CHECK(layers.size() == 3);
  CHECK(layers[1].front().id == 1);
  CHECK(layers[2].front().id == 3);
}
}  // namespace learning_test
