// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80061137;
  double density_weight = 0.20076676;
  double prefix_weight = 0.33338265;
  double neighborhood_weight = 0.18941410;
  double late_weight = 0.13124656;
  double critical_weight = 0.10012880;
  unsigned budget = 28;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
