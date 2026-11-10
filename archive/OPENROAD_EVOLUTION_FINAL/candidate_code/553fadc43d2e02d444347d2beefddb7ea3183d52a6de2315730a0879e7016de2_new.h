// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96197483;
  double density_weight = 0.52280181;
  double prefix_weight = 0.41912259;
  double neighborhood_weight = 0.13409361;
  double late_weight = 0.07588652;
  double critical_weight = 0.16857767;
  unsigned budget = 39;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
