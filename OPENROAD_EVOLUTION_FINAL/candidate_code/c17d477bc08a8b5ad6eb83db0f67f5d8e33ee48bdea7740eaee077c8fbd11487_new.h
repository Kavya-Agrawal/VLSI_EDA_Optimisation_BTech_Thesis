// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85170677;
  double density_weight = 0.14194677;
  double prefix_weight = 0.10852751;
  double neighborhood_weight = 0.38005159;
  double late_weight = 0.04461048;
  double critical_weight = 0.12987827;
  unsigned budget = 29;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
