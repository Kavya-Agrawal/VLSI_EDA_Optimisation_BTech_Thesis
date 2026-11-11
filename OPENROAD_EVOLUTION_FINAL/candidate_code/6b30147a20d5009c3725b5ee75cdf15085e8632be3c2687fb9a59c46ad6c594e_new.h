// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16629632;
  double density_weight = 0.15657947;
  double prefix_weight = 0.09227930;
  double neighborhood_weight = 0.30669075;
  double late_weight = 0.12564692;
  double critical_weight = 0.19388090;
  unsigned budget = 9;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
