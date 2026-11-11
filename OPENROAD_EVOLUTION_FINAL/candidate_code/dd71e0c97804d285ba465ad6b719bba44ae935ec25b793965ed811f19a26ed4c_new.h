// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65760072;
  double density_weight = 0.09784348;
  double prefix_weight = 0.13662834;
  double neighborhood_weight = 0.39843018;
  double late_weight = 0.11418347;
  double critical_weight = 0.31769613;
  unsigned budget = 18;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
