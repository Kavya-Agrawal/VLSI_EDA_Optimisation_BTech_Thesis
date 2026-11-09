// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63834952;
  double density_weight = 0.03108211;
  double prefix_weight = 0.41588702;
  double neighborhood_weight = 0.09749911;
  double late_weight = 0.06693861;
  double critical_weight = 0.12819381;
  unsigned budget = 30;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
