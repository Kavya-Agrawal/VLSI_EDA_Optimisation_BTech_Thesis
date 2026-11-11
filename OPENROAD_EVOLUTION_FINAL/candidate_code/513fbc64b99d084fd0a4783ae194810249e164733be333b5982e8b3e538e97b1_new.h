// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00973053;
  double density_weight = 0.57420728;
  double prefix_weight = 0.19779985;
  double neighborhood_weight = 0.26562714;
  double late_weight = 0.10479889;
  double critical_weight = 0.46884482;
  unsigned budget = 8;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
