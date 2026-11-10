// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55655156;
  double density_weight = 0.34983490;
  double prefix_weight = 0.49793561;
  double neighborhood_weight = 0.03379955;
  double late_weight = 0.01376206;
  double critical_weight = 0.40144675;
  unsigned budget = 13;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
