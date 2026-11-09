// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46605604;
  double density_weight = 0.37529646;
  double prefix_weight = 0.34448794;
  double neighborhood_weight = 0.32445050;
  double late_weight = 0.06235890;
  double critical_weight = 0.27543139;
  unsigned budget = 32;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
