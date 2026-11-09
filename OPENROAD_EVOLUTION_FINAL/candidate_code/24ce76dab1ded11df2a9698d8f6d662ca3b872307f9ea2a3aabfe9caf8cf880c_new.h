// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.40765841;
  double density_weight = 0.33355736;
  double prefix_weight = 0.17141018;
  double neighborhood_weight = 0.16817882;
  double late_weight = 0.15810716;
  double critical_weight = 0.14180507;
  unsigned budget = 22;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
