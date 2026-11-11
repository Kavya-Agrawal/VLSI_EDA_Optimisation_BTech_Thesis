// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73733595;
  double density_weight = 0.10166788;
  double prefix_weight = 0.46823252;
  double neighborhood_weight = 0.03576798;
  double late_weight = 0.28982569;
  double critical_weight = 0.25211034;
  unsigned budget = 22;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
