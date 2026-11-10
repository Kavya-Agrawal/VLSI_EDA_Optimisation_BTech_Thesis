// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.33505118;
  double density_weight = 0.17913609;
  double prefix_weight = 0.20402962;
  double neighborhood_weight = 0.38677557;
  double late_weight = 0.29871092;
  double critical_weight = 0.29879791;
  unsigned budget = 22;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
