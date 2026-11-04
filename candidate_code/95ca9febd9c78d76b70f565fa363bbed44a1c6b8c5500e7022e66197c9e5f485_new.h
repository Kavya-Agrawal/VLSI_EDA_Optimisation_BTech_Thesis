// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64198129;
  double density_weight = 0.24081106;
  double prefix_weight = 0.42561179;
  double neighborhood_weight = 0.33793441;
  double late_weight = 0.18725162;
  double critical_weight = 0.20294122;
  unsigned budget = 26;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
