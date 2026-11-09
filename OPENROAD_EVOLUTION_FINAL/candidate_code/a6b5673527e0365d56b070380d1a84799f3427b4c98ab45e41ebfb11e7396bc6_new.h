// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65874367;
  double density_weight = 0.01852938;
  double prefix_weight = 0.46332944;
  double neighborhood_weight = 0.39560516;
  double late_weight = 0.13797582;
  double critical_weight = 0.36289238;
  unsigned budget = 27;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
