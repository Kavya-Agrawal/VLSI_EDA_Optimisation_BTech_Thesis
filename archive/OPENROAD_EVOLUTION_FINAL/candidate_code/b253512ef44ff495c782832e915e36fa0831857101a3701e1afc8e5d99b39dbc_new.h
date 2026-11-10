// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93298704;
  double density_weight = 0.40222969;
  double prefix_weight = 0.05743310;
  double neighborhood_weight = 0.28418130;
  double late_weight = 0.21785357;
  double critical_weight = 0.01253600;
  unsigned budget = 16;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
