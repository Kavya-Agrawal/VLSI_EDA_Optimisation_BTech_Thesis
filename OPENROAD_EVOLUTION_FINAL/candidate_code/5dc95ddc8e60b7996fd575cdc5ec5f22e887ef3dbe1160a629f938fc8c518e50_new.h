// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62163407;
  double density_weight = 0.44523398;
  double prefix_weight = 0.07225761;
  double neighborhood_weight = 0.26363502;
  double late_weight = 0.27667694;
  double critical_weight = 0.29509092;
  unsigned budget = 10;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
