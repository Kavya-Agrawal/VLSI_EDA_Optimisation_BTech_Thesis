// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34885073;
  double density_weight = 0.28616784;
  double prefix_weight = 0.15628495;
  double neighborhood_weight = 0.21796247;
  double late_weight = 0.12434753;
  double critical_weight = 0.08313964;
  unsigned budget = 17;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
