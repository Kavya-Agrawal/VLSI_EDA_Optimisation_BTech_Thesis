// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79988507;
  double density_weight = 0.49218369;
  double prefix_weight = 0.49036547;
  double neighborhood_weight = 0.23067696;
  double late_weight = 0.13340542;
  double critical_weight = 0.07039695;
  unsigned budget = 16;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
