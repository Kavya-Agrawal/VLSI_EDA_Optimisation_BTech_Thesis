// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03651569;
  double density_weight = 0.25778976;
  double prefix_weight = 0.48429884;
  double neighborhood_weight = 0.09905694;
  double late_weight = 0.27595521;
  double critical_weight = 0.31266235;
  unsigned budget = 39;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
