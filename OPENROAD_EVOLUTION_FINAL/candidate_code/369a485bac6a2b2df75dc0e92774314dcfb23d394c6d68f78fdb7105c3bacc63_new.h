// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60898551;
  double density_weight = 0.21731834;
  double prefix_weight = 0.23820077;
  double neighborhood_weight = 0.27339158;
  double late_weight = 0.12482034;
  double critical_weight = 0.31467149;
  unsigned budget = 17;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
