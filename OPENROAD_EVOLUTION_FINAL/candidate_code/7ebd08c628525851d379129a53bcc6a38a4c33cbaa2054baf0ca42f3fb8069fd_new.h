// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43449949;
  double density_weight = 0.59220633;
  double prefix_weight = 0.14584291;
  double neighborhood_weight = 0.26563215;
  double late_weight = 0.16249473;
  double critical_weight = 0.18750935;
  unsigned budget = 33;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
