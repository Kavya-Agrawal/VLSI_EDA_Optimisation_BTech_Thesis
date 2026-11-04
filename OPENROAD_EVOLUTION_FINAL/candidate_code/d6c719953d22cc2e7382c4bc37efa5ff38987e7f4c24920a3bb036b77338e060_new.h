// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55698776;
  double density_weight = 0.31200571;
  double prefix_weight = 0.39819966;
  double neighborhood_weight = 0.08108609;
  double late_weight = 0.05943499;
  double critical_weight = 0.32392032;
  unsigned budget = 4;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
