// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74854475;
  double density_weight = 0.31831486;
  double prefix_weight = 0.00544058;
  double neighborhood_weight = 0.27616162;
  double late_weight = 0.08735914;
  double critical_weight = 0.18639117;
  unsigned budget = 21;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
