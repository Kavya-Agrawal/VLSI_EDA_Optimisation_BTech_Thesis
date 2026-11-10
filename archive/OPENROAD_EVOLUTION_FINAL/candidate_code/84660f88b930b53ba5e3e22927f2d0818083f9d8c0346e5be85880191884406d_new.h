// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85945163;
  double density_weight = 0.04370745;
  double prefix_weight = 0.23138115;
  double neighborhood_weight = 0.06776093;
  double late_weight = 0.10261191;
  double critical_weight = 0.09442507;
  unsigned budget = 26;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
