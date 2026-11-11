// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86899542;
  double density_weight = 0.22652391;
  double prefix_weight = 0.23266424;
  double neighborhood_weight = 0.10871414;
  double late_weight = 0.26885806;
  double critical_weight = 0.13909810;
  unsigned budget = 10;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
