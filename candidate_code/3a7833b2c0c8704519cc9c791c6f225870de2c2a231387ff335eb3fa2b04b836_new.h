// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12932807;
  double density_weight = 0.12193899;
  double prefix_weight = 0.22731564;
  double neighborhood_weight = 0.06229070;
  double late_weight = 0.20152619;
  double critical_weight = 0.25753835;
  unsigned budget = 20;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
