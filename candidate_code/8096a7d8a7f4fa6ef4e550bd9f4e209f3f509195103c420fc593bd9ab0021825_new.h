// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36717328;
  double density_weight = 0.27668317;
  double prefix_weight = 0.49390720;
  double neighborhood_weight = 0.04722340;
  double late_weight = 0.22781362;
  double critical_weight = 0.30817161;
  unsigned budget = 29;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
