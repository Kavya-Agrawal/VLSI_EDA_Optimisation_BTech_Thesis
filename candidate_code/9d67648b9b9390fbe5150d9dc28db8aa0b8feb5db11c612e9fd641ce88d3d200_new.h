// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78153712;
  double density_weight = 0.41948083;
  double prefix_weight = 0.33052117;
  double neighborhood_weight = 0.25323985;
  double late_weight = 0.15283033;
  double critical_weight = 0.44281673;
  unsigned budget = 17;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
