// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29233025;
  double density_weight = 0.25603509;
  double prefix_weight = 0.03898864;
  double neighborhood_weight = 0.17494338;
  double late_weight = 0.04199092;
  double critical_weight = 0.00191879;
  unsigned budget = 40;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
