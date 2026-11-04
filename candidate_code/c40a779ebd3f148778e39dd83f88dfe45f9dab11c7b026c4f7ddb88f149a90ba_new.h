// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17925943;
  double density_weight = 0.51494705;
  double prefix_weight = 0.42247082;
  double neighborhood_weight = 0.16350016;
  double late_weight = 0.00391768;
  double critical_weight = 0.07602690;
  unsigned budget = 32;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
