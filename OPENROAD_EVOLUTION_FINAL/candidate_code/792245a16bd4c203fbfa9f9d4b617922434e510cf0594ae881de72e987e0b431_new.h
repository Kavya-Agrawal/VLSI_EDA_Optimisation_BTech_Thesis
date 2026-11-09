// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37054825;
  double density_weight = 0.14459301;
  double prefix_weight = 0.08954343;
  double neighborhood_weight = 0.16386453;
  double late_weight = 0.06157240;
  double critical_weight = 0.47012549;
  unsigned budget = 21;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
