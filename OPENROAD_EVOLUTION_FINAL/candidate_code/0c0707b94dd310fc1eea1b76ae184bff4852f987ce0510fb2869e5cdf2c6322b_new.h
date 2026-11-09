// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21164625;
  double density_weight = 0.00517033;
  double prefix_weight = 0.26762028;
  double neighborhood_weight = 0.04577511;
  double late_weight = 0.15146349;
  double critical_weight = 0.27143670;
  unsigned budget = 15;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
