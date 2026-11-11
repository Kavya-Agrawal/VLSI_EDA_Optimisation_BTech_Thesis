// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18899743;
  double density_weight = 0.16371127;
  double prefix_weight = 0.21143696;
  double neighborhood_weight = 0.14690661;
  double late_weight = 0.12118095;
  double critical_weight = 0.14392737;
  unsigned budget = 25;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
