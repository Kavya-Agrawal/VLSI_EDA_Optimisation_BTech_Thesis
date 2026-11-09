// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43665167;
  double density_weight = 0.34420352;
  double prefix_weight = 0.03975209;
  double neighborhood_weight = 0.01906122;
  double late_weight = 0.12449531;
  double critical_weight = 0.32834345;
  unsigned budget = 23;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
