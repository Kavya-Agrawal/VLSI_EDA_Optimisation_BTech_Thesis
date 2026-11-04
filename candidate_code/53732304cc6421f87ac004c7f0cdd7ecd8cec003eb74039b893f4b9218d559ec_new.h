// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31269061;
  double density_weight = 0.56041011;
  double prefix_weight = 0.30609214;
  double neighborhood_weight = 0.35819925;
  double late_weight = 0.21971571;
  double critical_weight = 0.28944901;
  unsigned budget = 18;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
