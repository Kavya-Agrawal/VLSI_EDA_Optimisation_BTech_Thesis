// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31810092;
  double density_weight = 0.06402240;
  double prefix_weight = 0.12316179;
  double neighborhood_weight = 0.15584661;
  double late_weight = 0.18912631;
  double critical_weight = 0.09507922;
  unsigned budget = 27;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
