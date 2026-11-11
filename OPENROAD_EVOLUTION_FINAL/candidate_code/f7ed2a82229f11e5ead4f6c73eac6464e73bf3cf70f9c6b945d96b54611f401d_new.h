// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93640708;
  double density_weight = 0.51581149;
  double prefix_weight = 0.36576254;
  double neighborhood_weight = 0.26631613;
  double late_weight = 0.01187112;
  double critical_weight = 0.25214224;
  unsigned budget = 31;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
