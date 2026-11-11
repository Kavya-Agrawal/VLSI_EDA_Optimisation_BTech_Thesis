// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10465281;
  double density_weight = 0.29435355;
  double prefix_weight = 0.20196613;
  double neighborhood_weight = 0.33447690;
  double late_weight = 0.11653693;
  double critical_weight = 0.29553008;
  unsigned budget = 7;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
