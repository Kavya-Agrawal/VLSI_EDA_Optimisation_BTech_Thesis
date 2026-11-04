// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45459568;
  double density_weight = 0.54375179;
  double prefix_weight = 0.05261155;
  double neighborhood_weight = 0.32166544;
  double late_weight = 0.03813274;
  double critical_weight = 0.24256986;
  unsigned budget = 40;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
