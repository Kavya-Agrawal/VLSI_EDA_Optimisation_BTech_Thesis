// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16501680;
  double density_weight = 0.44173598;
  double prefix_weight = 0.33984254;
  double neighborhood_weight = 0.23875436;
  double late_weight = 0.09649267;
  double critical_weight = 0.36585267;
  unsigned budget = 14;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
