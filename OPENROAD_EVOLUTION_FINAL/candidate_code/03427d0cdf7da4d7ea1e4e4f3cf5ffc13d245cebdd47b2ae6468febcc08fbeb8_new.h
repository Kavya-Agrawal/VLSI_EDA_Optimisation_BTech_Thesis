// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.81856657;
  double density_weight = 0.35638145;
  double prefix_weight = 0.29151555;
  double neighborhood_weight = 0.31702756;
  double late_weight = 0.20647544;
  double critical_weight = 0.30757840;
  unsigned budget = 24;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
