// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92444033;
  double density_weight = 0.57336549;
  double prefix_weight = 0.01071741;
  double neighborhood_weight = 0.12034988;
  double late_weight = 0.11473471;
  double critical_weight = 0.05235062;
  unsigned budget = 36;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
