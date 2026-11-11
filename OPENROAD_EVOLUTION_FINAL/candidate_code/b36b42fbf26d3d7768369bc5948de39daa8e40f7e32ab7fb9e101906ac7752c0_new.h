// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.06861381;
  double density_weight = 0.53198550;
  double prefix_weight = 0.42142670;
  double neighborhood_weight = 0.20019012;
  double late_weight = 0.18393511;
  double critical_weight = 0.32024435;
  unsigned budget = 26;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
