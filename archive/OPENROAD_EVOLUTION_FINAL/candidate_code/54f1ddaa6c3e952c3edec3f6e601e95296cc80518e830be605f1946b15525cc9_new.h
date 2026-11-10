// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58491349;
  double density_weight = 0.25936550;
  double prefix_weight = 0.28644442;
  double neighborhood_weight = 0.24362105;
  double late_weight = 0.23805684;
  double critical_weight = 0.22733683;
  unsigned budget = 21;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
