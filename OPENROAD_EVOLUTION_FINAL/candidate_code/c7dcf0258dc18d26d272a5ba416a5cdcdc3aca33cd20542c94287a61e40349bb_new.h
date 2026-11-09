// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10210913;
  double density_weight = 0.31284720;
  double prefix_weight = 0.22249576;
  double neighborhood_weight = 0.28316204;
  double late_weight = 0.05914679;
  double critical_weight = 0.47658647;
  unsigned budget = 12;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
