// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73086542;
  double density_weight = 0.39407448;
  double prefix_weight = 0.22669132;
  double neighborhood_weight = 0.04847147;
  double late_weight = 0.03484292;
  double critical_weight = 0.22623158;
  unsigned budget = 16;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
