// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16084818;
  double density_weight = 0.46362251;
  double prefix_weight = 0.46521475;
  double neighborhood_weight = 0.27115251;
  double late_weight = 0.15034685;
  double critical_weight = 0.06116857;
  unsigned budget = 7;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
