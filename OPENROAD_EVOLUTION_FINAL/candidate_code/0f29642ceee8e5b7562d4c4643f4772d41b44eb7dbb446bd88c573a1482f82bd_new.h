// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.75328756;
  double density_weight = 0.31880827;
  double prefix_weight = 0.09387989;
  double neighborhood_weight = 0.09788136;
  double late_weight = 0.26808341;
  double critical_weight = 0.44928808;
  unsigned budget = 32;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
