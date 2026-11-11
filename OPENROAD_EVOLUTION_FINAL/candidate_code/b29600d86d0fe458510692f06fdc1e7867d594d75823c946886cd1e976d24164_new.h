// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89786241;
  double density_weight = 0.04415245;
  double prefix_weight = 0.14001635;
  double neighborhood_weight = 0.34614446;
  double late_weight = 0.15996431;
  double critical_weight = 0.49781186;
  unsigned budget = 37;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
