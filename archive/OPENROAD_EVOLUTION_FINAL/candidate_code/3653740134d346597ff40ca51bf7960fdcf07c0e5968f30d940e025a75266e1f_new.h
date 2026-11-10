// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54852296;
  double density_weight = 0.27043394;
  double prefix_weight = 0.23004534;
  double neighborhood_weight = 0.29587083;
  double late_weight = 0.12864357;
  double critical_weight = 0.48635749;
  unsigned budget = 37;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
