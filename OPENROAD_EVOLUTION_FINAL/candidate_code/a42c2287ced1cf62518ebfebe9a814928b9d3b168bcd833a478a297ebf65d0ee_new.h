// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93789443;
  double density_weight = 0.45455111;
  double prefix_weight = 0.33418525;
  double neighborhood_weight = 0.34251714;
  double late_weight = 0.00255440;
  double critical_weight = 0.41317339;
  unsigned budget = 29;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
