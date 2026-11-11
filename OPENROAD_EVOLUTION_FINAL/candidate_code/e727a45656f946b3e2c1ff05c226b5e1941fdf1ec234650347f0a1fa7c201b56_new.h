// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16488598;
  double density_weight = 0.58240004;
  double prefix_weight = 0.43730620;
  double neighborhood_weight = 0.39456333;
  double late_weight = 0.00903967;
  double critical_weight = 0.27690219;
  unsigned budget = 7;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
