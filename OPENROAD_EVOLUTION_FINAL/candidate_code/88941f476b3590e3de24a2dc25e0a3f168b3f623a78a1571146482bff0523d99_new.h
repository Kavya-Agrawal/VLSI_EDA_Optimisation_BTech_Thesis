// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89663042;
  double density_weight = 0.51257957;
  double prefix_weight = 0.06153853;
  double neighborhood_weight = 0.02784102;
  double late_weight = 0.24234526;
  double critical_weight = 0.17117506;
  unsigned budget = 22;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
