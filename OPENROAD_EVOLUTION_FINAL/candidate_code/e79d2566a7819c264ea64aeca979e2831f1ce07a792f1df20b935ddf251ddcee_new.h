// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23539310;
  double density_weight = 0.33405892;
  double prefix_weight = 0.45932771;
  double neighborhood_weight = 0.32368195;
  double late_weight = 0.28378693;
  double critical_weight = 0.27173806;
  unsigned budget = 40;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
