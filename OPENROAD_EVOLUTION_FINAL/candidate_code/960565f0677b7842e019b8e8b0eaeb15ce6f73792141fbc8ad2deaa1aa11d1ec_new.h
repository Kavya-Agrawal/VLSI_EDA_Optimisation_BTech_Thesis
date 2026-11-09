// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72195147;
  double density_weight = 0.26077235;
  double prefix_weight = 0.12911657;
  double neighborhood_weight = 0.18984303;
  double late_weight = 0.05411762;
  double critical_weight = 0.20499936;
  unsigned budget = 20;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
