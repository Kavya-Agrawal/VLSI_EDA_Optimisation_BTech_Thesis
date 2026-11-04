// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18929804;
  double density_weight = 0.50459442;
  double prefix_weight = 0.32820277;
  double neighborhood_weight = 0.10470020;
  double late_weight = 0.16731171;
  double critical_weight = 0.32935380;
  unsigned budget = 14;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
