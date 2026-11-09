// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73255123;
  double density_weight = 0.23344234;
  double prefix_weight = 0.18616025;
  double neighborhood_weight = 0.08332108;
  double late_weight = 0.07662771;
  double critical_weight = 0.23231375;
  unsigned budget = 15;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
