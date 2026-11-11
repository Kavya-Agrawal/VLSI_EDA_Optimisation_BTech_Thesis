// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.39388516;
  double density_weight = 0.17693769;
  double prefix_weight = 0.21894786;
  double neighborhood_weight = 0.34073319;
  double late_weight = 0.14724697;
  double critical_weight = 0.25923517;
  unsigned budget = 15;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
