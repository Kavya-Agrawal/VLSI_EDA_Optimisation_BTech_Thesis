// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10343107;
  double density_weight = 0.02970511;
  double prefix_weight = 0.37770688;
  double neighborhood_weight = 0.36254198;
  double late_weight = 0.12547321;
  double critical_weight = 0.05522441;
  unsigned budget = 20;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
