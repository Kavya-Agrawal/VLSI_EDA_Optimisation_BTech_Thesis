// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.91433121;
  double density_weight = 0.18188466;
  double prefix_weight = 0.18475668;
  double neighborhood_weight = 0.03755020;
  double late_weight = 0.12395648;
  double critical_weight = 0.21267349;
  unsigned budget = 32;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
