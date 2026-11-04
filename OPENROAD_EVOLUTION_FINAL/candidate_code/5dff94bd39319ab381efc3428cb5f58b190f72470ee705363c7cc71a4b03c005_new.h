// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09751989;
  double density_weight = 0.43640649;
  double prefix_weight = 0.05679125;
  double neighborhood_weight = 0.30145039;
  double late_weight = 0.26052877;
  double critical_weight = 0.16254467;
  unsigned budget = 12;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
