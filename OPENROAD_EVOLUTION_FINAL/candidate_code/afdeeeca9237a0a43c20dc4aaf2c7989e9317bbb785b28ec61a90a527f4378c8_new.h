// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87148001;
  double density_weight = 0.47639917;
  double prefix_weight = 0.14495687;
  double neighborhood_weight = 0.08230543;
  double late_weight = 0.25078498;
  double critical_weight = 0.31322757;
  unsigned budget = 23;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
