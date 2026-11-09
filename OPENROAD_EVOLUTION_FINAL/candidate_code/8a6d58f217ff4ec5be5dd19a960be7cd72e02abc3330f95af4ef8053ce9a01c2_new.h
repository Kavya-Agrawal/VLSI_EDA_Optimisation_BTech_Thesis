// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58218117;
  double density_weight = 0.12667631;
  double prefix_weight = 0.15654045;
  double neighborhood_weight = 0.20296987;
  double late_weight = 0.14079283;
  double critical_weight = 0.15182124;
  unsigned budget = 30;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
