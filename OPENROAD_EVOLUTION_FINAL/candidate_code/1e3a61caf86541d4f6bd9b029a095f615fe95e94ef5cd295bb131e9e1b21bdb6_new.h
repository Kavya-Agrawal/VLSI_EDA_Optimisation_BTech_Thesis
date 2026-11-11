// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61189397;
  double density_weight = 0.06286848;
  double prefix_weight = 0.45977890;
  double neighborhood_weight = 0.30050677;
  double late_weight = 0.17587301;
  double critical_weight = 0.04966140;
  unsigned budget = 16;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
