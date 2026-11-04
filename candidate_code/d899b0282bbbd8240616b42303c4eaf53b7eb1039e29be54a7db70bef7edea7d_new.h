// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59350251;
  double density_weight = 0.41094468;
  double prefix_weight = 0.20090921;
  double neighborhood_weight = 0.04755577;
  double late_weight = 0.22210121;
  double critical_weight = 0.27102280;
  unsigned budget = 37;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
