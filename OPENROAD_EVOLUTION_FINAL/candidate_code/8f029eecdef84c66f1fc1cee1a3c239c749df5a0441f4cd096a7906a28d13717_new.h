// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.49699958;
  double density_weight = 0.05509462;
  double prefix_weight = 0.38193653;
  double neighborhood_weight = 0.09361570;
  double late_weight = 0.19392756;
  double critical_weight = 0.44333240;
  unsigned budget = 16;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
