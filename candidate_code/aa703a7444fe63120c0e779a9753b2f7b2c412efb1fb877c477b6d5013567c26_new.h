// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35999798;
  double density_weight = 0.27476604;
  double prefix_weight = 0.05728853;
  double neighborhood_weight = 0.25694573;
  double late_weight = 0.13300195;
  double critical_weight = 0.04107842;
  unsigned budget = 13;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
