// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43526318;
  double density_weight = 0.21345375;
  double prefix_weight = 0.21655112;
  double neighborhood_weight = 0.06889659;
  double late_weight = 0.25864842;
  double critical_weight = 0.42892626;
  unsigned budget = 30;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
