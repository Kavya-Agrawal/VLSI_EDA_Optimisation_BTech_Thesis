// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03952691;
  double density_weight = 0.54944260;
  double prefix_weight = 0.31227578;
  double neighborhood_weight = 0.03280387;
  double late_weight = 0.02840658;
  double critical_weight = 0.33463956;
  unsigned budget = 40;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
