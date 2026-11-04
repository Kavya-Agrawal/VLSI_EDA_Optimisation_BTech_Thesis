// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02837867;
  double density_weight = 0.19085671;
  double prefix_weight = 0.07640001;
  double neighborhood_weight = 0.08348482;
  double late_weight = 0.15355470;
  double critical_weight = 0.09157400;
  unsigned budget = 16;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
