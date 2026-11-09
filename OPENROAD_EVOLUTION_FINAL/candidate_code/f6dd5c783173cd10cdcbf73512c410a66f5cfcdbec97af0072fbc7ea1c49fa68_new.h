// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.77964964;
  double density_weight = 0.28584864;
  double prefix_weight = 0.27033770;
  double neighborhood_weight = 0.08115609;
  double late_weight = 0.10911572;
  double critical_weight = 0.32626487;
  unsigned budget = 33;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
