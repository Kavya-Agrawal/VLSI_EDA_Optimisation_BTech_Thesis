// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97478153;
  double density_weight = 0.07964454;
  double prefix_weight = 0.26568018;
  double neighborhood_weight = 0.21189922;
  double late_weight = 0.01716365;
  double critical_weight = 0.12198622;
  unsigned budget = 26;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
