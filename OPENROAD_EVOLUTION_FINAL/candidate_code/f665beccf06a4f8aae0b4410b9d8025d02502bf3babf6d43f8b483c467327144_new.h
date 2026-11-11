// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02848444;
  double density_weight = 0.55048859;
  double prefix_weight = 0.07026955;
  double neighborhood_weight = 0.15975379;
  double late_weight = 0.27025777;
  double critical_weight = 0.06894417;
  unsigned budget = 14;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
