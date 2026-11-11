// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51003503;
  double density_weight = 0.15550075;
  double prefix_weight = 0.25769913;
  double neighborhood_weight = 0.21870933;
  double late_weight = 0.22517379;
  double critical_weight = 0.12561709;
  unsigned budget = 16;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
