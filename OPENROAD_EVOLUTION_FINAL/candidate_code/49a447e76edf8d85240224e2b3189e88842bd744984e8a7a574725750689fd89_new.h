// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02004887;
  double density_weight = 0.12734102;
  double prefix_weight = 0.43683236;
  double neighborhood_weight = 0.37503935;
  double late_weight = 0.25384970;
  double critical_weight = 0.40865142;
  unsigned budget = 27;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
