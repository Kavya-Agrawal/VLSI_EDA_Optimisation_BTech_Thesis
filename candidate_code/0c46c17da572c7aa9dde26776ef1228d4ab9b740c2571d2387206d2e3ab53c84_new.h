// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27609526;
  double density_weight = 0.56518109;
  double prefix_weight = 0.22966224;
  double neighborhood_weight = 0.23153629;
  double late_weight = 0.13847274;
  double critical_weight = 0.13557993;
  unsigned budget = 10;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
