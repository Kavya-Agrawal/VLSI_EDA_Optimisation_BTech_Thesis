// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41464834;
  double density_weight = 0.51192387;
  double prefix_weight = 0.36398068;
  double neighborhood_weight = 0.00801905;
  double late_weight = 0.14147355;
  double critical_weight = 0.16555400;
  unsigned budget = 11;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
