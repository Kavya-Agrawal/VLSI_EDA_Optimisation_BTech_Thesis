// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51385651;
  double density_weight = 0.39192774;
  double prefix_weight = 0.43233763;
  double neighborhood_weight = 0.37723194;
  double late_weight = 0.11913428;
  double critical_weight = 0.00306666;
  unsigned budget = 23;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
