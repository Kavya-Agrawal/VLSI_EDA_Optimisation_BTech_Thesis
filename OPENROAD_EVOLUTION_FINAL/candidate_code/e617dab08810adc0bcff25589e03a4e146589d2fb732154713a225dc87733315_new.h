// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13334261;
  double density_weight = 0.51984773;
  double prefix_weight = 0.32953556;
  double neighborhood_weight = 0.29653161;
  double late_weight = 0.12268791;
  double critical_weight = 0.24299201;
  unsigned budget = 24;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
