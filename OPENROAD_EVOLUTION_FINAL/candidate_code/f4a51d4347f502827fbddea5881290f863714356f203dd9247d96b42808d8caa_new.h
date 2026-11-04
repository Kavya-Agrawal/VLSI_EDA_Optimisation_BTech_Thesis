// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34092512;
  double density_weight = 0.37037047;
  double prefix_weight = 0.15443385;
  double neighborhood_weight = 0.32257324;
  double late_weight = 0.18286990;
  double critical_weight = 0.23919867;
  unsigned budget = 10;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
