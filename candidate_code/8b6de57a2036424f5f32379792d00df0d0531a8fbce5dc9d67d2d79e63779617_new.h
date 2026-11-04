// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90569213;
  double density_weight = 0.09596176;
  double prefix_weight = 0.32933272;
  double neighborhood_weight = 0.26855975;
  double late_weight = 0.11257440;
  double critical_weight = 0.00835845;
  unsigned budget = 6;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
