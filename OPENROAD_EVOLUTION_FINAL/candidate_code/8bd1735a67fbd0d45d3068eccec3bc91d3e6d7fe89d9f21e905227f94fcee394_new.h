// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37001788;
  double density_weight = 0.08106283;
  double prefix_weight = 0.30030407;
  double neighborhood_weight = 0.23323425;
  double late_weight = 0.24647187;
  double critical_weight = 0.48372882;
  unsigned budget = 14;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
