// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.63425430;
  double density_weight = 0.22878024;
  double prefix_weight = 0.10776396;
  double neighborhood_weight = 0.37837660;
  double late_weight = 0.00549593;
  double critical_weight = 0.41287189;
  unsigned budget = 17;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
