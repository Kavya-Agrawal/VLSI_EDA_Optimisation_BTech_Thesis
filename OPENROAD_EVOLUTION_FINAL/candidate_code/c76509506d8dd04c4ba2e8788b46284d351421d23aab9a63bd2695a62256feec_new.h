// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74025833;
  double density_weight = 0.26798303;
  double prefix_weight = 0.36749541;
  double neighborhood_weight = 0.37015017;
  double late_weight = 0.26309520;
  double critical_weight = 0.31877532;
  unsigned budget = 22;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
