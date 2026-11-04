// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99607784;
  double density_weight = 0.07370244;
  double prefix_weight = 0.28263945;
  double neighborhood_weight = 0.11002312;
  double late_weight = 0.00278957;
  double critical_weight = 0.37817973;
  unsigned budget = 20;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
