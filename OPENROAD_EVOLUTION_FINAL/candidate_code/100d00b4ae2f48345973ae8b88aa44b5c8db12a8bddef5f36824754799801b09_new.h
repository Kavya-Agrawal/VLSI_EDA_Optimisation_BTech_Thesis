// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87080757;
  double density_weight = 0.13595344;
  double prefix_weight = 0.05823027;
  double neighborhood_weight = 0.37055624;
  double late_weight = 0.02315825;
  double critical_weight = 0.44100581;
  unsigned budget = 32;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
