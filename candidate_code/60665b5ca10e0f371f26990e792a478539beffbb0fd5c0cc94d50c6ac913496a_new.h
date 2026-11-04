// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55388938;
  double density_weight = 0.12788333;
  double prefix_weight = 0.21261177;
  double neighborhood_weight = 0.10796470;
  double late_weight = 0.19914490;
  double critical_weight = 0.03528697;
  unsigned budget = 34;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
