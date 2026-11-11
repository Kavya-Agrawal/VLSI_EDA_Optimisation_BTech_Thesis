// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71539260;
  double density_weight = 0.22657636;
  double prefix_weight = 0.35081263;
  double neighborhood_weight = 0.00499861;
  double late_weight = 0.23927602;
  double critical_weight = 0.22569043;
  unsigned budget = 4;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
