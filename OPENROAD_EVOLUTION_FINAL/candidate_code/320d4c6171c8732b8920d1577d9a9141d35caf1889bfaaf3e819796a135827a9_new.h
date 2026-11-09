// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12085829;
  double density_weight = 0.09005372;
  double prefix_weight = 0.35802144;
  double neighborhood_weight = 0.14282125;
  double late_weight = 0.24245182;
  double critical_weight = 0.22802182;
  unsigned budget = 18;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
