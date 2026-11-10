// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29207412;
  double density_weight = 0.41687434;
  double prefix_weight = 0.04061934;
  double neighborhood_weight = 0.10652076;
  double late_weight = 0.00988795;
  double critical_weight = 0.46508192;
  unsigned budget = 22;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
