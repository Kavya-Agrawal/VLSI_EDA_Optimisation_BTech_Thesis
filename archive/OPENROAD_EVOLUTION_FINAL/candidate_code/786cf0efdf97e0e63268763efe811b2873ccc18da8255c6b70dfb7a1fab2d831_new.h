// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21025517;
  double density_weight = 0.26664978;
  double prefix_weight = 0.37609924;
  double neighborhood_weight = 0.17218714;
  double late_weight = 0.08907019;
  double critical_weight = 0.49439751;
  unsigned budget = 28;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
