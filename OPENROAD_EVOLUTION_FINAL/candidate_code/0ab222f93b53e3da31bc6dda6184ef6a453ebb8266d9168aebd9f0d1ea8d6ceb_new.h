// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.53883855;
  double density_weight = 0.19594387;
  double prefix_weight = 0.46055658;
  double neighborhood_weight = 0.16436829;
  double late_weight = 0.08813562;
  double critical_weight = 0.40582019;
  unsigned budget = 38;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
