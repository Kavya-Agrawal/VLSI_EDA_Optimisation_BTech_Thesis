// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79321514;
  double density_weight = 0.16612764;
  double prefix_weight = 0.28819126;
  double neighborhood_weight = 0.32194792;
  double late_weight = 0.03332631;
  double critical_weight = 0.21490812;
  unsigned budget = 24;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
