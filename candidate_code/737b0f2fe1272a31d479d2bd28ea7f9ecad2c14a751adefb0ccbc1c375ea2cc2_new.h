// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61462809;
  double density_weight = 0.37663887;
  double prefix_weight = 0.37400139;
  double neighborhood_weight = 0.11572329;
  double late_weight = 0.18673359;
  double critical_weight = 0.36997925;
  unsigned budget = 7;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
