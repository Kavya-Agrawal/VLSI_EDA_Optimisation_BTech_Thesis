// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98067809;
  double density_weight = 0.50671276;
  double prefix_weight = 0.01289939;
  double neighborhood_weight = 0.11305210;
  double late_weight = 0.06402176;
  double critical_weight = 0.42349285;
  unsigned budget = 16;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
