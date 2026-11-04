// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.49139174;
  double density_weight = 0.20572044;
  double prefix_weight = 0.10903460;
  double neighborhood_weight = 0.16387578;
  double late_weight = 0.29883585;
  double critical_weight = 0.05297451;
  unsigned budget = 31;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
