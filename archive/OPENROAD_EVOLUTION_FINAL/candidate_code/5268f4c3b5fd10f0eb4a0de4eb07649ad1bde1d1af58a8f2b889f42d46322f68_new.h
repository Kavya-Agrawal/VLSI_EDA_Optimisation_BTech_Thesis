// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56220322;
  double density_weight = 0.51743580;
  double prefix_weight = 0.12758710;
  double neighborhood_weight = 0.02635746;
  double late_weight = 0.23247745;
  double critical_weight = 0.46206456;
  unsigned budget = 36;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
