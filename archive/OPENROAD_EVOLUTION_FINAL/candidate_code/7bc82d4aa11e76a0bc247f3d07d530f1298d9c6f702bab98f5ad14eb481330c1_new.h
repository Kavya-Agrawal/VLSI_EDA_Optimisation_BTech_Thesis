// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09378971;
  double density_weight = 0.40247272;
  double prefix_weight = 0.23880527;
  double neighborhood_weight = 0.00544131;
  double late_weight = 0.08465867;
  double critical_weight = 0.32572254;
  unsigned budget = 8;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
