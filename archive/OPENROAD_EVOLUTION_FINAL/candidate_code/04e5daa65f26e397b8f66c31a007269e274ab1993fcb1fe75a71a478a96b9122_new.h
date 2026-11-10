// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56244761;
  double density_weight = 0.55356500;
  double prefix_weight = 0.39458563;
  double neighborhood_weight = 0.19958765;
  double late_weight = 0.19342462;
  double critical_weight = 0.13473131;
  unsigned budget = 9;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
