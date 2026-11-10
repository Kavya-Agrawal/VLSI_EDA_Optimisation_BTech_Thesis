// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36793071;
  double density_weight = 0.32107784;
  double prefix_weight = 0.29266775;
  double neighborhood_weight = 0.19040348;
  double late_weight = 0.02615791;
  double critical_weight = 0.30897600;
  unsigned budget = 27;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
