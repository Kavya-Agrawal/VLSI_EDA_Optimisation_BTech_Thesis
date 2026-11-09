// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46454928;
  double density_weight = 0.06688188;
  double prefix_weight = 0.06528392;
  double neighborhood_weight = 0.36721678;
  double late_weight = 0.22879434;
  double critical_weight = 0.21595671;
  unsigned budget = 37;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
