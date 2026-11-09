// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70133801;
  double density_weight = 0.50653228;
  double prefix_weight = 0.30166381;
  double neighborhood_weight = 0.24789396;
  double late_weight = 0.21179289;
  double critical_weight = 0.30437189;
  unsigned budget = 7;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
