// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46622262;
  double density_weight = 0.28382822;
  double prefix_weight = 0.36681898;
  double neighborhood_weight = 0.23646818;
  double late_weight = 0.19223371;
  double critical_weight = 0.03551102;
  unsigned budget = 20;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
