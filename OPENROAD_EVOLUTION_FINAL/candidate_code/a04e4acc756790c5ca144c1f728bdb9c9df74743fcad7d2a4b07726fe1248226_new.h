// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24950144;
  double density_weight = 0.05338212;
  double prefix_weight = 0.46757944;
  double neighborhood_weight = 0.26746404;
  double late_weight = 0.07976908;
  double critical_weight = 0.47954861;
  unsigned budget = 12;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
