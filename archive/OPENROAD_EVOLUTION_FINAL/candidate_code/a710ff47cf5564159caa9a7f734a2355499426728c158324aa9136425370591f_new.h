// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27451734;
  double density_weight = 0.52635317;
  double prefix_weight = 0.33621054;
  double neighborhood_weight = 0.21120218;
  double late_weight = 0.27192150;
  double critical_weight = 0.35082604;
  unsigned budget = 26;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
