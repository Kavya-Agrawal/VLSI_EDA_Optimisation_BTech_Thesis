// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.91970044;
  double density_weight = 0.50663010;
  double prefix_weight = 0.31036456;
  double neighborhood_weight = 0.31805220;
  double late_weight = 0.04951585;
  double critical_weight = 0.04435554;
  unsigned budget = 29;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
