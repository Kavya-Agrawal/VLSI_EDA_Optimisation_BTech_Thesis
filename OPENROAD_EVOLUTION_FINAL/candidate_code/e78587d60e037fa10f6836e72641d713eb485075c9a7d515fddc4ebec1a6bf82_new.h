// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64911887;
  double density_weight = 0.35083736;
  double prefix_weight = 0.06873627;
  double neighborhood_weight = 0.32646060;
  double late_weight = 0.09697501;
  double critical_weight = 0.22188476;
  unsigned budget = 32;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
