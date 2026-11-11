// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19628153;
  double density_weight = 0.59748132;
  double prefix_weight = 0.49973746;
  double neighborhood_weight = 0.31208609;
  double late_weight = 0.10762148;
  double critical_weight = 0.33325446;
  unsigned budget = 8;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
