// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.40795719;
  double density_weight = 0.39555641;
  double prefix_weight = 0.38290773;
  double neighborhood_weight = 0.04746122;
  double late_weight = 0.05026071;
  double critical_weight = 0.27477410;
  unsigned budget = 17;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
