// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38959996;
  double density_weight = 0.12086947;
  double prefix_weight = 0.44511999;
  double neighborhood_weight = 0.30705815;
  double late_weight = 0.19700998;
  double critical_weight = 0.21040237;
  unsigned budget = 26;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
