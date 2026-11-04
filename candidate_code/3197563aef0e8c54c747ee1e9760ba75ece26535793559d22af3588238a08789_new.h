// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.95242887;
  double density_weight = 0.48447540;
  double prefix_weight = 0.45491271;
  double neighborhood_weight = 0.27059322;
  double late_weight = 0.20205808;
  double critical_weight = 0.16225334;
  unsigned budget = 6;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
