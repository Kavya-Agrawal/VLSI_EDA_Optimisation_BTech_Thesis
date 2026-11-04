// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64428689;
  double density_weight = 0.22145084;
  double prefix_weight = 0.19688303;
  double neighborhood_weight = 0.38436454;
  double late_weight = 0.17763979;
  double critical_weight = 0.28338764;
  unsigned budget = 16;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
