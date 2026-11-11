// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84544575;
  double density_weight = 0.56504507;
  double prefix_weight = 0.22541484;
  double neighborhood_weight = 0.38342337;
  double late_weight = 0.09224297;
  double critical_weight = 0.12142465;
  unsigned budget = 40;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
