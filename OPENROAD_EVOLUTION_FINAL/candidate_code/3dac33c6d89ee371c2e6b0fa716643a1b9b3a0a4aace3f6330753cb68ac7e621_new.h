// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24242731;
  double density_weight = 0.39444717;
  double prefix_weight = 0.02174018;
  double neighborhood_weight = 0.32076703;
  double late_weight = 0.00795414;
  double critical_weight = 0.14589205;
  unsigned budget = 31;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
