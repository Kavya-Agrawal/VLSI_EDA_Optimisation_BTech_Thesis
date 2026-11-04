// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10068710;
  double density_weight = 0.47951018;
  double prefix_weight = 0.48457039;
  double neighborhood_weight = 0.06162149;
  double late_weight = 0.19468380;
  double critical_weight = 0.30484845;
  unsigned budget = 15;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
