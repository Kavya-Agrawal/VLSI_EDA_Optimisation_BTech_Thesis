// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27960455;
  double density_weight = 0.56438185;
  double prefix_weight = 0.38842197;
  double neighborhood_weight = 0.35005851;
  double late_weight = 0.03449324;
  double critical_weight = 0.08075831;
  unsigned budget = 37;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
