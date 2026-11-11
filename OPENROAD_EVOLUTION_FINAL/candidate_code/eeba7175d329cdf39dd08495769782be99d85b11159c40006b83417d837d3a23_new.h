// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15943697;
  double density_weight = 0.54833591;
  double prefix_weight = 0.35742800;
  double neighborhood_weight = 0.15631720;
  double late_weight = 0.07296625;
  double critical_weight = 0.37507957;
  unsigned budget = 26;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
