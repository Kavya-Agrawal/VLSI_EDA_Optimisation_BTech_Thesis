// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45725385;
  double density_weight = 0.30957187;
  double prefix_weight = 0.39529745;
  double neighborhood_weight = 0.30236244;
  double late_weight = 0.17501309;
  double critical_weight = 0.49963745;
  unsigned budget = 19;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
