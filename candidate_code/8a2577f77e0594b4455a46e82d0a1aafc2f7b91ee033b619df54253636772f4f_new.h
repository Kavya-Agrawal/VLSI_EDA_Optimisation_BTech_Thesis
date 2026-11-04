// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.95238550;
  double density_weight = 0.35647945;
  double prefix_weight = 0.35887682;
  double neighborhood_weight = 0.29369391;
  double late_weight = 0.04260130;
  double critical_weight = 0.32958165;
  unsigned budget = 25;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
