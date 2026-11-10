// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29383160;
  double density_weight = 0.34919201;
  double prefix_weight = 0.26875779;
  double neighborhood_weight = 0.24809415;
  double late_weight = 0.19811332;
  double critical_weight = 0.40671580;
  unsigned budget = 30;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
