// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52840339;
  double density_weight = 0.04918598;
  double prefix_weight = 0.41789557;
  double neighborhood_weight = 0.23465116;
  double late_weight = 0.06936650;
  double critical_weight = 0.36235766;
  unsigned budget = 18;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
