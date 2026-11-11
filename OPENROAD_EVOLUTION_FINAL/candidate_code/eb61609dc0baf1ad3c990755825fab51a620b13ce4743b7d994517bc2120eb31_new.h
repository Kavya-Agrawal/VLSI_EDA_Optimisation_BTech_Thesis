// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.05818698;
  double density_weight = 0.04359523;
  double prefix_weight = 0.16928189;
  double neighborhood_weight = 0.17976249;
  double late_weight = 0.21124370;
  double critical_weight = 0.17586017;
  unsigned budget = 39;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
