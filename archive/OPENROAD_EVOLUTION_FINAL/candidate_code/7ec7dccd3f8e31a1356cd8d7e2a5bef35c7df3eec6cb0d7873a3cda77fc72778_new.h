// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21852904;
  double density_weight = 0.21912134;
  double prefix_weight = 0.34683774;
  double neighborhood_weight = 0.21807185;
  double late_weight = 0.20253841;
  double critical_weight = 0.25127094;
  unsigned budget = 24;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
