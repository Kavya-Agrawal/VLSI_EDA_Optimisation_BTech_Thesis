// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80285531;
  double density_weight = 0.38976186;
  double prefix_weight = 0.36529124;
  double neighborhood_weight = 0.04810464;
  double late_weight = 0.24165092;
  double critical_weight = 0.26937855;
  unsigned budget = 33;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
