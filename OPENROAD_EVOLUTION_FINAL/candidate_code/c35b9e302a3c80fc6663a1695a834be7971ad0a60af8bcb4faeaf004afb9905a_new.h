// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72654597;
  double density_weight = 0.13915286;
  double prefix_weight = 0.04216326;
  double neighborhood_weight = 0.23794451;
  double late_weight = 0.23521103;
  double critical_weight = 0.28175041;
  unsigned budget = 12;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
