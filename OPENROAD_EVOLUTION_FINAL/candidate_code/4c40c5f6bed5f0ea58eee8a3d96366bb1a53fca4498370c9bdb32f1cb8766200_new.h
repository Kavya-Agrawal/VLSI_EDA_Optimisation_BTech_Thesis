// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46374482;
  double density_weight = 0.13373253;
  double prefix_weight = 0.17645173;
  double neighborhood_weight = 0.34285687;
  double late_weight = 0.11369830;
  double critical_weight = 0.32072651;
  unsigned budget = 33;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
