// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78687681;
  double density_weight = 0.24789078;
  double prefix_weight = 0.14790947;
  double neighborhood_weight = 0.32987434;
  double late_weight = 0.29196720;
  double critical_weight = 0.46766062;
  unsigned budget = 5;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
