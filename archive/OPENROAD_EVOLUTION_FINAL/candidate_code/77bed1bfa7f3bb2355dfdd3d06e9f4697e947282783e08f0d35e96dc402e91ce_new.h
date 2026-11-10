// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57055227;
  double density_weight = 0.51154070;
  double prefix_weight = 0.29797672;
  double neighborhood_weight = 0.20663479;
  double late_weight = 0.22143862;
  double critical_weight = 0.32154665;
  unsigned budget = 37;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
