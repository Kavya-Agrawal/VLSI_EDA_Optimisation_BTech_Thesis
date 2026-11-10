// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76721544;
  double density_weight = 0.58359840;
  double prefix_weight = 0.46523463;
  double neighborhood_weight = 0.19121730;
  double late_weight = 0.23052062;
  double critical_weight = 0.00168752;
  unsigned budget = 36;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
