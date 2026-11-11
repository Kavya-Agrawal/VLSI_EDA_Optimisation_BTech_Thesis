// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01728920;
  double density_weight = 0.38712519;
  double prefix_weight = 0.48867795;
  double neighborhood_weight = 0.35380237;
  double late_weight = 0.13871737;
  double critical_weight = 0.42813050;
  unsigned budget = 37;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
