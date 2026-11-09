// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44671445;
  double density_weight = 0.44461566;
  double prefix_weight = 0.01804392;
  double neighborhood_weight = 0.15054706;
  double late_weight = 0.24652322;
  double critical_weight = 0.34529970;
  unsigned budget = 12;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
