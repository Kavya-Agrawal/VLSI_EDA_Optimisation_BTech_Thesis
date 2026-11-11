// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41371316;
  double density_weight = 0.32002781;
  double prefix_weight = 0.16599654;
  double neighborhood_weight = 0.09695371;
  double late_weight = 0.10683882;
  double critical_weight = 0.32009745;
  unsigned budget = 13;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
