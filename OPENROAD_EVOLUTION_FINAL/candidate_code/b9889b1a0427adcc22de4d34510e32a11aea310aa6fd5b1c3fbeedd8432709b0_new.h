// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14087867;
  double density_weight = 0.27307342;
  double prefix_weight = 0.29375385;
  double neighborhood_weight = 0.33189285;
  double late_weight = 0.04957095;
  double critical_weight = 0.16322662;
  unsigned budget = 11;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
