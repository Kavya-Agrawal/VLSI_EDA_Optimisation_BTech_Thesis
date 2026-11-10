// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.50303695;
  double density_weight = 0.18075174;
  double prefix_weight = 0.43040875;
  double neighborhood_weight = 0.10747431;
  double late_weight = 0.17263921;
  double critical_weight = 0.09582336;
  unsigned budget = 6;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
