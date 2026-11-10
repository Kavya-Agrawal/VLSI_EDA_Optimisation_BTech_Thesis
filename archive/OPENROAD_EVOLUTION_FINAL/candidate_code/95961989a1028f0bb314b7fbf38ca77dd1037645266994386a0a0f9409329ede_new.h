// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87372107;
  double density_weight = 0.53571893;
  double prefix_weight = 0.05845774;
  double neighborhood_weight = 0.14995334;
  double late_weight = 0.02898576;
  double critical_weight = 0.06157956;
  unsigned budget = 13;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
