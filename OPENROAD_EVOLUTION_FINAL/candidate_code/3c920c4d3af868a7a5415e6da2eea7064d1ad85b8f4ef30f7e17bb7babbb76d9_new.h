// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84735966;
  double density_weight = 0.07543665;
  double prefix_weight = 0.06991387;
  double neighborhood_weight = 0.17183868;
  double late_weight = 0.14098205;
  double critical_weight = 0.11534752;
  unsigned budget = 23;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
