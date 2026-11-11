// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18742432;
  double density_weight = 0.06726510;
  double prefix_weight = 0.45596904;
  double neighborhood_weight = 0.35727209;
  double late_weight = 0.23388899;
  double critical_weight = 0.21394684;
  unsigned budget = 10;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
