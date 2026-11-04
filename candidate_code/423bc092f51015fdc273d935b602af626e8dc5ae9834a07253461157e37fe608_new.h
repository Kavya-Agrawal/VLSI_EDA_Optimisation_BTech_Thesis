// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92349938;
  double density_weight = 0.37919862;
  double prefix_weight = 0.15026870;
  double neighborhood_weight = 0.33040045;
  double late_weight = 0.28650328;
  double critical_weight = 0.27260854;
  unsigned budget = 9;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
