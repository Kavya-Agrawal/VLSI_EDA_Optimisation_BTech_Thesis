// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17891021;
  double density_weight = 0.51122883;
  double prefix_weight = 0.16413519;
  double neighborhood_weight = 0.05082678;
  double late_weight = 0.01146707;
  double critical_weight = 0.44751541;
  unsigned budget = 33;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
