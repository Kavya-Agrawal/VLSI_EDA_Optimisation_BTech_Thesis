// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37746401;
  double density_weight = 0.49172712;
  double prefix_weight = 0.27181140;
  double neighborhood_weight = 0.12818225;
  double late_weight = 0.24351185;
  double critical_weight = 0.45378128;
  unsigned budget = 20;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
