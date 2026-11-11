// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12923408;
  double density_weight = 0.55561548;
  double prefix_weight = 0.42626774;
  double neighborhood_weight = 0.11249929;
  double late_weight = 0.27568213;
  double critical_weight = 0.45222046;
  unsigned budget = 25;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
