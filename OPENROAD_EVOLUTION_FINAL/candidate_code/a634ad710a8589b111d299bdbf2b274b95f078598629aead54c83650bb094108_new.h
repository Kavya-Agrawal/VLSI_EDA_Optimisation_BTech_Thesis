// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.68620882;
  double density_weight = 0.29265193;
  double prefix_weight = 0.02615846;
  double neighborhood_weight = 0.06895486;
  double late_weight = 0.18546002;
  double critical_weight = 0.09619153;
  unsigned budget = 10;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
