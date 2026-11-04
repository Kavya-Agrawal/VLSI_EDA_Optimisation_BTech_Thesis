// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.40061608;
  double density_weight = 0.14310550;
  double prefix_weight = 0.16333496;
  double neighborhood_weight = 0.02954003;
  double late_weight = 0.00390466;
  double critical_weight = 0.21186226;
  unsigned budget = 28;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
