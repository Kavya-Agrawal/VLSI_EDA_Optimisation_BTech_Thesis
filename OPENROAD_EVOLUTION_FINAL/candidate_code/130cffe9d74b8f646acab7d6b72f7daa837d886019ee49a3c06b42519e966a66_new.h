// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86268768;
  double density_weight = 0.02959470;
  double prefix_weight = 0.14410151;
  double neighborhood_weight = 0.38063347;
  double late_weight = 0.07292853;
  double critical_weight = 0.25795123;
  unsigned budget = 26;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
