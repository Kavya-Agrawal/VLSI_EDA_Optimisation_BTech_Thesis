// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90409955;
  double density_weight = 0.08619621;
  double prefix_weight = 0.30901911;
  double neighborhood_weight = 0.10368706;
  double late_weight = 0.10023910;
  double critical_weight = 0.42112040;
  unsigned budget = 5;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
