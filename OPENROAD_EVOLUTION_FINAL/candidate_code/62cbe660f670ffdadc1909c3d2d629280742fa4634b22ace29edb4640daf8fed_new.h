// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70554761;
  double density_weight = 0.25305020;
  double prefix_weight = 0.45977089;
  double neighborhood_weight = 0.17967561;
  double late_weight = 0.18498044;
  double critical_weight = 0.44936232;
  unsigned budget = 20;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
