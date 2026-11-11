// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94467317;
  double density_weight = 0.52712525;
  double prefix_weight = 0.33336349;
  double neighborhood_weight = 0.17185160;
  double late_weight = 0.03708209;
  double critical_weight = 0.13743897;
  unsigned budget = 39;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
