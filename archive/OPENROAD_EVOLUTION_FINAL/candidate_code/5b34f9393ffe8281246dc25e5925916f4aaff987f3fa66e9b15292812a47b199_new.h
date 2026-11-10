// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80794301;
  double density_weight = 0.03925201;
  double prefix_weight = 0.03499415;
  double neighborhood_weight = 0.34447763;
  double late_weight = 0.12560441;
  double critical_weight = 0.06579218;
  unsigned budget = 18;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
