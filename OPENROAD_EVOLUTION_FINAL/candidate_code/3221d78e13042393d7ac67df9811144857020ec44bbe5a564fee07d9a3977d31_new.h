// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56327494;
  double density_weight = 0.34330900;
  double prefix_weight = 0.47714988;
  double neighborhood_weight = 0.27328452;
  double late_weight = 0.10515526;
  double critical_weight = 0.26621407;
  unsigned budget = 25;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
