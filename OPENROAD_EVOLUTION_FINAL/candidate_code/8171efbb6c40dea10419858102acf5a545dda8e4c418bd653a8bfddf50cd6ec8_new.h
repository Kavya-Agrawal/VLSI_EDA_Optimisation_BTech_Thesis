// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64472995;
  double density_weight = 0.27348500;
  double prefix_weight = 0.05221464;
  double neighborhood_weight = 0.19783606;
  double late_weight = 0.06858022;
  double critical_weight = 0.19750896;
  unsigned budget = 22;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
