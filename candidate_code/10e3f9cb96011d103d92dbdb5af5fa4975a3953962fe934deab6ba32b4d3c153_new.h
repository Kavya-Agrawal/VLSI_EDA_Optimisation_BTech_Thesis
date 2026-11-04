// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.75246630;
  double density_weight = 0.36998435;
  double prefix_weight = 0.04219796;
  double neighborhood_weight = 0.20331026;
  double late_weight = 0.02089948;
  double critical_weight = 0.24942023;
  unsigned budget = 26;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
