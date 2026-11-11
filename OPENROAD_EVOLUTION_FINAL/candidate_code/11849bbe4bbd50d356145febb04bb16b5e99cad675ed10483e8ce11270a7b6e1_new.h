// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45482958;
  double density_weight = 0.43327889;
  double prefix_weight = 0.18812706;
  double neighborhood_weight = 0.15354220;
  double late_weight = 0.26284769;
  double critical_weight = 0.05607796;
  unsigned budget = 29;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
