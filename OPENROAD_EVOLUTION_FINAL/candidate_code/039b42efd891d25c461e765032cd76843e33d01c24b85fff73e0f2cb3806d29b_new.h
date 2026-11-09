// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60027595;
  double density_weight = 0.44790120;
  double prefix_weight = 0.38619499;
  double neighborhood_weight = 0.12696239;
  double late_weight = 0.02910567;
  double critical_weight = 0.18964693;
  unsigned budget = 36;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
