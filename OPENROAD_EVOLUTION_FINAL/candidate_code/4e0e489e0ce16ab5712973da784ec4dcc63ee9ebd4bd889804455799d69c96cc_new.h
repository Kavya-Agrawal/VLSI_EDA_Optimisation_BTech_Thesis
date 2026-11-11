// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82536535;
  double density_weight = 0.08920893;
  double prefix_weight = 0.34088025;
  double neighborhood_weight = 0.35563472;
  double late_weight = 0.19772641;
  double critical_weight = 0.11907594;
  unsigned budget = 36;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
