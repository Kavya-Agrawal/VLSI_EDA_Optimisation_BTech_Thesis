// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51693641;
  double density_weight = 0.53882539;
  double prefix_weight = 0.02012261;
  double neighborhood_weight = 0.34703617;
  double late_weight = 0.09995087;
  double critical_weight = 0.34468859;
  unsigned budget = 12;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
