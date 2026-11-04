// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23652830;
  double density_weight = 0.11594842;
  double prefix_weight = 0.44972777;
  double neighborhood_weight = 0.26855517;
  double late_weight = 0.27186404;
  double critical_weight = 0.33254253;
  unsigned budget = 14;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
