// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73490743;
  double density_weight = 0.15628249;
  double prefix_weight = 0.41632379;
  double neighborhood_weight = 0.37894733;
  double late_weight = 0.00970861;
  double critical_weight = 0.01514025;
  unsigned budget = 6;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
