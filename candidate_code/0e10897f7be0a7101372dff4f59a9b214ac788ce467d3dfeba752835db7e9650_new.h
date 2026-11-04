// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51718006;
  double density_weight = 0.06641777;
  double prefix_weight = 0.22788556;
  double neighborhood_weight = 0.08206626;
  double late_weight = 0.07786169;
  double critical_weight = 0.12520620;
  unsigned budget = 11;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
