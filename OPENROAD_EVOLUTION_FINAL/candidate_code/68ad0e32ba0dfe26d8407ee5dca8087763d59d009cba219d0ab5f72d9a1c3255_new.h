// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41212758;
  double density_weight = 0.48178211;
  double prefix_weight = 0.10121945;
  double neighborhood_weight = 0.03916803;
  double late_weight = 0.02589163;
  double critical_weight = 0.25726699;
  unsigned budget = 27;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
