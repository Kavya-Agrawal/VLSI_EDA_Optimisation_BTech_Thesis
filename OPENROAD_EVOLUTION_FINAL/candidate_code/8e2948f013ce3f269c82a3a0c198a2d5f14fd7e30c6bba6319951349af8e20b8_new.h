// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35209995;
  double density_weight = 0.16427190;
  double prefix_weight = 0.21608952;
  double neighborhood_weight = 0.20263909;
  double late_weight = 0.10753335;
  double critical_weight = 0.09798882;
  unsigned budget = 20;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
