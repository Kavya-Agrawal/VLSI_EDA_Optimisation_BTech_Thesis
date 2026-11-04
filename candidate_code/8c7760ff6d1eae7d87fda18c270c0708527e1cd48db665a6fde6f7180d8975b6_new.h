// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10888932;
  double density_weight = 0.13115701;
  double prefix_weight = 0.09327348;
  double neighborhood_weight = 0.07810429;
  double late_weight = 0.01305671;
  double critical_weight = 0.35997009;
  unsigned budget = 24;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
