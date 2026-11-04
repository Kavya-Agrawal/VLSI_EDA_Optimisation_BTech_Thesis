// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15608489;
  double density_weight = 0.45423326;
  double prefix_weight = 0.23064789;
  double neighborhood_weight = 0.19594343;
  double late_weight = 0.23796138;
  double critical_weight = 0.07266480;
  unsigned budget = 34;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
