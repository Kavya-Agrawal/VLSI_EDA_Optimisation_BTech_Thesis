// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96274951;
  double density_weight = 0.16564746;
  double prefix_weight = 0.35772493;
  double neighborhood_weight = 0.05172724;
  double late_weight = 0.03736328;
  double critical_weight = 0.30644082;
  unsigned budget = 13;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
