// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07685284;
  double density_weight = 0.29246619;
  double prefix_weight = 0.38206777;
  double neighborhood_weight = 0.16742152;
  double late_weight = 0.24272895;
  double critical_weight = 0.32832494;
  unsigned budget = 18;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
