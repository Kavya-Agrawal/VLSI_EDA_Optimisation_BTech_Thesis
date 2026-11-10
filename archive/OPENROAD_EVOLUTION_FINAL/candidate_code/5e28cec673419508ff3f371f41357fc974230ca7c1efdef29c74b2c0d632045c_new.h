// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58721243;
  double density_weight = 0.50285096;
  double prefix_weight = 0.04730024;
  double neighborhood_weight = 0.12423788;
  double late_weight = 0.18221504;
  double critical_weight = 0.37701285;
  unsigned budget = 12;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
