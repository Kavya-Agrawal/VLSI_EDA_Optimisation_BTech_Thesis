// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02025865;
  double density_weight = 0.27310045;
  double prefix_weight = 0.08874519;
  double neighborhood_weight = 0.29221500;
  double late_weight = 0.28708681;
  double critical_weight = 0.10502464;
  unsigned budget = 38;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
