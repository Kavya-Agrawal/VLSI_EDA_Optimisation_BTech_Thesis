// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18939187;
  double density_weight = 0.08388001;
  double prefix_weight = 0.30079345;
  double neighborhood_weight = 0.35970485;
  double late_weight = 0.11029794;
  double critical_weight = 0.03187640;
  unsigned budget = 23;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
