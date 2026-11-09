// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55648603;
  double density_weight = 0.42664034;
  double prefix_weight = 0.31943088;
  double neighborhood_weight = 0.09598657;
  double late_weight = 0.01379453;
  double critical_weight = 0.46459868;
  unsigned budget = 33;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
