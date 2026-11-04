// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35882377;
  double density_weight = 0.36723956;
  double prefix_weight = 0.44731559;
  double neighborhood_weight = 0.25571041;
  double late_weight = 0.08381288;
  double critical_weight = 0.28140009;
  unsigned budget = 28;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
