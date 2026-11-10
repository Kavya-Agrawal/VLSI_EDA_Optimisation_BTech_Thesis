// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46191313;
  double density_weight = 0.19801442;
  double prefix_weight = 0.17906702;
  double neighborhood_weight = 0.27354629;
  double late_weight = 0.07404648;
  double critical_weight = 0.02142639;
  unsigned budget = 9;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
