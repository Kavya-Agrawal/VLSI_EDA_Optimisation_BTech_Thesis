// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48222991;
  double density_weight = 0.39592509;
  double prefix_weight = 0.10496739;
  double neighborhood_weight = 0.08752386;
  double late_weight = 0.11066125;
  double critical_weight = 0.33597573;
  unsigned budget = 34;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
