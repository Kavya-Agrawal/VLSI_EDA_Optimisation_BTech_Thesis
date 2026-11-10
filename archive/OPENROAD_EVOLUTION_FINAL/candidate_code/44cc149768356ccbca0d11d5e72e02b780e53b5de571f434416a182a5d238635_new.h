// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.26169705;
  double density_weight = 0.20911123;
  double prefix_weight = 0.08750775;
  double neighborhood_weight = 0.30922794;
  double late_weight = 0.13944225;
  double critical_weight = 0.23282068;
  unsigned budget = 20;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
