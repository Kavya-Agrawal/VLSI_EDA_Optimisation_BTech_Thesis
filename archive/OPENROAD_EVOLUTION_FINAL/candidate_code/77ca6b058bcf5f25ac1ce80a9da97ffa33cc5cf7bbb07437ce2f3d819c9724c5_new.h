// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13908409;
  double density_weight = 0.28517368;
  double prefix_weight = 0.19698447;
  double neighborhood_weight = 0.16415181;
  double late_weight = 0.10955806;
  double critical_weight = 0.27953087;
  unsigned budget = 36;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
