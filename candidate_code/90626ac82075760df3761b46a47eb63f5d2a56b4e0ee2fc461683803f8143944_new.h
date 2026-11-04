// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94196208;
  double density_weight = 0.20277542;
  double prefix_weight = 0.28302651;
  double neighborhood_weight = 0.10379908;
  double late_weight = 0.09260735;
  double critical_weight = 0.09390054;
  unsigned budget = 22;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
