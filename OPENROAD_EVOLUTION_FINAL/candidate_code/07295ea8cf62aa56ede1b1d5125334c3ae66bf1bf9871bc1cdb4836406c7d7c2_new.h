// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.06585110;
  double density_weight = 0.14446547;
  double prefix_weight = 0.43238073;
  double neighborhood_weight = 0.22945087;
  double late_weight = 0.16986595;
  double critical_weight = 0.10721966;
  unsigned budget = 36;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
