// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.53593236;
  double density_weight = 0.51347975;
  double prefix_weight = 0.44182119;
  double neighborhood_weight = 0.32023980;
  double late_weight = 0.12564754;
  double critical_weight = 0.39470567;
  unsigned budget = 7;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
