// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82953234;
  double density_weight = 0.56320894;
  double prefix_weight = 0.19214067;
  double neighborhood_weight = 0.39634079;
  double late_weight = 0.24630095;
  double critical_weight = 0.47789506;
  unsigned budget = 14;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
