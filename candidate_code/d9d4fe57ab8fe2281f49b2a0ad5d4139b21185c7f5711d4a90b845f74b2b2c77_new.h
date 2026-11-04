// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56722073;
  double density_weight = 0.59272119;
  double prefix_weight = 0.15342780;
  double neighborhood_weight = 0.18690696;
  double late_weight = 0.20325761;
  double critical_weight = 0.33436705;
  unsigned budget = 8;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
