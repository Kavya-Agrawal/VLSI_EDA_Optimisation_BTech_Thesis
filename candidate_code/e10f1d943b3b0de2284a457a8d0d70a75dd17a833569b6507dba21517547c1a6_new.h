// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10136502;
  double density_weight = 0.20659618;
  double prefix_weight = 0.22148474;
  double neighborhood_weight = 0.17323982;
  double late_weight = 0.01503954;
  double critical_weight = 0.34089442;
  unsigned budget = 11;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
