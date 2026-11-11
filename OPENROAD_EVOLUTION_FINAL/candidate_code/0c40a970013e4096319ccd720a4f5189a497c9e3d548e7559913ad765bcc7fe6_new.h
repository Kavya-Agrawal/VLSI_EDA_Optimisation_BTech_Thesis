// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73293124;
  double density_weight = 0.31291618;
  double prefix_weight = 0.11398526;
  double neighborhood_weight = 0.00201675;
  double late_weight = 0.05978063;
  double critical_weight = 0.33047876;
  unsigned budget = 32;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
