// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19091351;
  double density_weight = 0.26661177;
  double prefix_weight = 0.15718408;
  double neighborhood_weight = 0.36297601;
  double late_weight = 0.01918856;
  double critical_weight = 0.22702504;
  unsigned budget = 14;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
