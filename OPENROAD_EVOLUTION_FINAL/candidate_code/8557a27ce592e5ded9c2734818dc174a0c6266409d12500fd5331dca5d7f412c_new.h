// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55787149;
  double density_weight = 0.50172786;
  double prefix_weight = 0.42858472;
  double neighborhood_weight = 0.08551300;
  double late_weight = 0.10613764;
  double critical_weight = 0.43423652;
  unsigned budget = 27;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
