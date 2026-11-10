// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58995192;
  double density_weight = 0.51763227;
  double prefix_weight = 0.46441824;
  double neighborhood_weight = 0.25031691;
  double late_weight = 0.17875485;
  double critical_weight = 0.26752741;
  unsigned budget = 7;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
