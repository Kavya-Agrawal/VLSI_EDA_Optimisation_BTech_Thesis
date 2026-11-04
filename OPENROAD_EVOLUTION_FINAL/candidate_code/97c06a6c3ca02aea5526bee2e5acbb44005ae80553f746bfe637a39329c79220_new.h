// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34627274;
  double density_weight = 0.01676942;
  double prefix_weight = 0.48873994;
  double neighborhood_weight = 0.15401051;
  double late_weight = 0.24559844;
  double critical_weight = 0.00133267;
  unsigned budget = 36;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
