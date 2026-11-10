// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.68381636;
  double density_weight = 0.31128514;
  double prefix_weight = 0.14528295;
  double neighborhood_weight = 0.33640701;
  double late_weight = 0.19086416;
  double critical_weight = 0.26896488;
  unsigned budget = 40;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
