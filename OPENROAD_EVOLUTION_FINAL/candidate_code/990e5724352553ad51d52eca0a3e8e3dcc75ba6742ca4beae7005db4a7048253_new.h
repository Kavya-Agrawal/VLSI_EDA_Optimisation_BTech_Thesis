// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17313563;
  double density_weight = 0.35510506;
  double prefix_weight = 0.40070479;
  double neighborhood_weight = 0.07809709;
  double late_weight = 0.28595099;
  double critical_weight = 0.28986772;
  unsigned budget = 11;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
