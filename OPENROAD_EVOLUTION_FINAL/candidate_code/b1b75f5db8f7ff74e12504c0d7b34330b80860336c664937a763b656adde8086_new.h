// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57593503;
  double density_weight = 0.37497459;
  double prefix_weight = 0.18842885;
  double neighborhood_weight = 0.31637031;
  double late_weight = 0.09598426;
  double critical_weight = 0.03241510;
  unsigned budget = 26;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
