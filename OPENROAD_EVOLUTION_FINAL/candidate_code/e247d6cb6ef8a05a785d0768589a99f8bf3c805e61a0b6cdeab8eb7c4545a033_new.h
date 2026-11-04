// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36878103;
  double density_weight = 0.28341433;
  double prefix_weight = 0.35119104;
  double neighborhood_weight = 0.06686963;
  double late_weight = 0.23256456;
  double critical_weight = 0.15860957;
  unsigned budget = 25;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
