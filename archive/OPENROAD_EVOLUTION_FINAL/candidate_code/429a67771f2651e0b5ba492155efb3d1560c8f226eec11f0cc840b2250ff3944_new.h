// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89333195;
  double density_weight = 0.33512056;
  double prefix_weight = 0.00616994;
  double neighborhood_weight = 0.35168626;
  double late_weight = 0.12790720;
  double critical_weight = 0.07567413;
  unsigned budget = 22;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
