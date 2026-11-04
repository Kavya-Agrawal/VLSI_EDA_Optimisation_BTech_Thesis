// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55671400;
  double density_weight = 0.10839092;
  double prefix_weight = 0.15149326;
  double neighborhood_weight = 0.39345532;
  double late_weight = 0.25646101;
  double critical_weight = 0.01639853;
  unsigned budget = 26;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
