// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04251771;
  double density_weight = 0.46147998;
  double prefix_weight = 0.26531511;
  double neighborhood_weight = 0.22557603;
  double late_weight = 0.06598868;
  double critical_weight = 0.48575705;
  unsigned budget = 12;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
