// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21370486;
  double density_weight = 0.17444766;
  double prefix_weight = 0.17298406;
  double neighborhood_weight = 0.15483449;
  double late_weight = 0.01826176;
  double critical_weight = 0.35761494;
  unsigned budget = 27;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
