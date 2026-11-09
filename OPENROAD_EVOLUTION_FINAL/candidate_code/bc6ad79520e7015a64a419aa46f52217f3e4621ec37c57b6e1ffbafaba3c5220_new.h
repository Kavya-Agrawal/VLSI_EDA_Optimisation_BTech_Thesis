// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10027275;
  double density_weight = 0.14301093;
  double prefix_weight = 0.30519294;
  double neighborhood_weight = 0.17101752;
  double late_weight = 0.10290039;
  double critical_weight = 0.41708089;
  unsigned budget = 32;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
