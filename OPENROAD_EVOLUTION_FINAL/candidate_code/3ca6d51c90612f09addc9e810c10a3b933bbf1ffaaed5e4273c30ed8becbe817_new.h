// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.00273087;
  double density_weight = 0.00502220;
  double prefix_weight = 0.00050569;
  double neighborhood_weight = 0.28699174;
  double late_weight = 0.10649320;
  double critical_weight = 0.06501068;
  unsigned budget = 5;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
