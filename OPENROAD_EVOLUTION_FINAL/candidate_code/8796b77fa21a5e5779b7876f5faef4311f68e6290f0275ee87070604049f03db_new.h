// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03266367;
  double density_weight = 0.15355906;
  double prefix_weight = 0.02372678;
  double neighborhood_weight = 0.33789670;
  double late_weight = 0.03325233;
  double critical_weight = 0.32829887;
  unsigned budget = 10;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
