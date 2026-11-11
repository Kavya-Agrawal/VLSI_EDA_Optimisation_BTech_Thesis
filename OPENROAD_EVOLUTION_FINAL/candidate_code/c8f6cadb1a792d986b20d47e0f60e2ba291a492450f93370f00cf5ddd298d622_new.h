// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.50606135;
  double density_weight = 0.44678891;
  double prefix_weight = 0.44770427;
  double neighborhood_weight = 0.22270513;
  double late_weight = 0.06038560;
  double critical_weight = 0.21670723;
  unsigned budget = 11;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
