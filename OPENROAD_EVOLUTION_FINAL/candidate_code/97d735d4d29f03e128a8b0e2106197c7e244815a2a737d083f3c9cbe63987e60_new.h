// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18011661;
  double density_weight = 0.01298134;
  double prefix_weight = 0.02919687;
  double neighborhood_weight = 0.30561061;
  double late_weight = 0.29357091;
  double critical_weight = 0.16538320;
  unsigned budget = 32;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
