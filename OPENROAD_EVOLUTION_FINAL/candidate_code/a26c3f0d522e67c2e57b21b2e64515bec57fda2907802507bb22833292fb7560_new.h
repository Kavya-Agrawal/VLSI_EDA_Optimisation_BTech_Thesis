// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99671492;
  double density_weight = 0.16604562;
  double prefix_weight = 0.08111971;
  double neighborhood_weight = 0.15858841;
  double late_weight = 0.05982267;
  double critical_weight = 0.24013760;
  unsigned budget = 39;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
