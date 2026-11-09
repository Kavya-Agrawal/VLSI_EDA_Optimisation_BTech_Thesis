// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23341142;
  double density_weight = 0.00306895;
  double prefix_weight = 0.37093588;
  double neighborhood_weight = 0.21963028;
  double late_weight = 0.16133369;
  double critical_weight = 0.24564392;
  unsigned budget = 40;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
