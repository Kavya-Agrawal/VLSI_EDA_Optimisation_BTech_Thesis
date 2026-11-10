// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74392489;
  double density_weight = 0.15345995;
  double prefix_weight = 0.38206051;
  double neighborhood_weight = 0.31785146;
  double late_weight = 0.07421320;
  double critical_weight = 0.31224893;
  unsigned budget = 9;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
