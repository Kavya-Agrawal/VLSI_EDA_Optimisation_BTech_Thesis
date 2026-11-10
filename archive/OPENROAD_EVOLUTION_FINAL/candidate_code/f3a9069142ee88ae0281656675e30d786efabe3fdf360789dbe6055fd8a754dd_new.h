// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57495644;
  double density_weight = 0.54208500;
  double prefix_weight = 0.24678727;
  double neighborhood_weight = 0.05549483;
  double late_weight = 0.21781174;
  double critical_weight = 0.32857981;
  unsigned budget = 13;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
