// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37202212;
  double density_weight = 0.50102644;
  double prefix_weight = 0.05282600;
  double neighborhood_weight = 0.39140868;
  double late_weight = 0.11825563;
  double critical_weight = 0.12464497;
  unsigned budget = 33;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
