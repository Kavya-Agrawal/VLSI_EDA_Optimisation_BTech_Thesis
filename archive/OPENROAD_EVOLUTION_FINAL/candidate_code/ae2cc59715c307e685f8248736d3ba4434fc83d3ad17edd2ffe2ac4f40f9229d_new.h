// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57490258;
  double density_weight = 0.51051829;
  double prefix_weight = 0.29992609;
  double neighborhood_weight = 0.07169853;
  double late_weight = 0.15812184;
  double critical_weight = 0.07656336;
  unsigned budget = 17;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
