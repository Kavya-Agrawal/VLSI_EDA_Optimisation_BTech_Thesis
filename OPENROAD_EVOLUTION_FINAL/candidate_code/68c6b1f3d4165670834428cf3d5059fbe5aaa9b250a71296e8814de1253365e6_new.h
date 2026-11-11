// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23524280;
  double density_weight = 0.47294968;
  double prefix_weight = 0.26401506;
  double neighborhood_weight = 0.22033081;
  double late_weight = 0.16765144;
  double critical_weight = 0.27816180;
  unsigned budget = 24;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
