// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27503247;
  double density_weight = 0.16074417;
  double prefix_weight = 0.33931739;
  double neighborhood_weight = 0.08359363;
  double late_weight = 0.00049624;
  double critical_weight = 0.30664785;
  unsigned budget = 12;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
