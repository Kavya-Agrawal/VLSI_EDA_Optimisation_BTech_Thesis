// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.26433815;
  double density_weight = 0.12615243;
  double prefix_weight = 0.17942504;
  double neighborhood_weight = 0.23464857;
  double late_weight = 0.00848204;
  double critical_weight = 0.44817181;
  unsigned budget = 18;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
