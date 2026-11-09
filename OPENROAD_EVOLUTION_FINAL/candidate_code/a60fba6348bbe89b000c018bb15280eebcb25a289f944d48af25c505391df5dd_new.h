// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45050802;
  double density_weight = 0.31273232;
  double prefix_weight = 0.31857803;
  double neighborhood_weight = 0.23674990;
  double late_weight = 0.25901113;
  double critical_weight = 0.34929440;
  unsigned budget = 18;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
