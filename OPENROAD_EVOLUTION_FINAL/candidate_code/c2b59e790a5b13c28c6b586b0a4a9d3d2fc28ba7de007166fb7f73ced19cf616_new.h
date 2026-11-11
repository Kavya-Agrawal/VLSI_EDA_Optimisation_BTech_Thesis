// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60649154;
  double density_weight = 0.54214140;
  double prefix_weight = 0.47378805;
  double neighborhood_weight = 0.37612673;
  double late_weight = 0.15601714;
  double critical_weight = 0.37846491;
  unsigned budget = 12;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
