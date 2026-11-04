// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35301843;
  double density_weight = 0.50749132;
  double prefix_weight = 0.12681644;
  double neighborhood_weight = 0.03923051;
  double late_weight = 0.00426444;
  double critical_weight = 0.01224186;
  unsigned budget = 21;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
