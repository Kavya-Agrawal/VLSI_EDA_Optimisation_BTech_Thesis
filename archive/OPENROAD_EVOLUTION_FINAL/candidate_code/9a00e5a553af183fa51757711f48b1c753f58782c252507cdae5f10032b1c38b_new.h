// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96040070;
  double density_weight = 0.29774717;
  double prefix_weight = 0.23617770;
  double neighborhood_weight = 0.07846276;
  double late_weight = 0.25448745;
  double critical_weight = 0.23350301;
  unsigned budget = 33;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
