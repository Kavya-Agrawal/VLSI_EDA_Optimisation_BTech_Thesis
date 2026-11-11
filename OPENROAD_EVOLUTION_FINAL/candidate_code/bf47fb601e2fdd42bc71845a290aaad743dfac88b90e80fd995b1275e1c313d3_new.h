// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59692902;
  double density_weight = 0.39317513;
  double prefix_weight = 0.01651348;
  double neighborhood_weight = 0.01951206;
  double late_weight = 0.19408010;
  double critical_weight = 0.05754011;
  unsigned budget = 6;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
