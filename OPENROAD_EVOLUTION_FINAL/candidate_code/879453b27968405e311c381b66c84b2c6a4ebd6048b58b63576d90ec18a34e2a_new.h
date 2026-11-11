// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43833182;
  double density_weight = 0.36724456;
  double prefix_weight = 0.24767614;
  double neighborhood_weight = 0.00414061;
  double late_weight = 0.01892989;
  double critical_weight = 0.17990110;
  unsigned budget = 18;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
