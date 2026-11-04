// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.67326427;
  double density_weight = 0.18702412;
  double prefix_weight = 0.02533694;
  double neighborhood_weight = 0.16877106;
  double late_weight = 0.07394286;
  double critical_weight = 0.08048997;
  unsigned budget = 32;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
