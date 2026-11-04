// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98506772;
  double density_weight = 0.27728729;
  double prefix_weight = 0.40354759;
  double neighborhood_weight = 0.27667352;
  double late_weight = 0.03506857;
  double critical_weight = 0.22755871;
  unsigned budget = 21;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
