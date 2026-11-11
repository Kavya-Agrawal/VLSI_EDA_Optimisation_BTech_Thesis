// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13283241;
  double density_weight = 0.10972629;
  double prefix_weight = 0.23842450;
  double neighborhood_weight = 0.23304289;
  double late_weight = 0.20860017;
  double critical_weight = 0.26668358;
  unsigned budget = 16;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
