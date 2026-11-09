// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76546475;
  double density_weight = 0.10196561;
  double prefix_weight = 0.13701937;
  double neighborhood_weight = 0.29557158;
  double late_weight = 0.25304823;
  double critical_weight = 0.17597164;
  unsigned budget = 4;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
