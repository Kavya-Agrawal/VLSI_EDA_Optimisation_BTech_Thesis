// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97868752;
  double density_weight = 0.12540258;
  double prefix_weight = 0.35566546;
  double neighborhood_weight = 0.18997294;
  double late_weight = 0.21123266;
  double critical_weight = 0.12166319;
  unsigned budget = 7;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
