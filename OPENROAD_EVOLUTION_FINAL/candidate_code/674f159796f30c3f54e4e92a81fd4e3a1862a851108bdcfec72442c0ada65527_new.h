// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59332848;
  double density_weight = 0.05455935;
  double prefix_weight = 0.03522137;
  double neighborhood_weight = 0.10230328;
  double late_weight = 0.13832138;
  double critical_weight = 0.47207289;
  unsigned budget = 18;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
