// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25338536;
  double density_weight = 0.49838010;
  double prefix_weight = 0.10580834;
  double neighborhood_weight = 0.32934607;
  double late_weight = 0.26351603;
  double critical_weight = 0.12927212;
  unsigned budget = 39;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
