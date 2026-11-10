// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.53188071;
  double density_weight = 0.37339331;
  double prefix_weight = 0.20417819;
  double neighborhood_weight = 0.30481757;
  double late_weight = 0.22342222;
  double critical_weight = 0.31780183;
  unsigned budget = 8;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
