// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.53838762;
  double density_weight = 0.11430857;
  double prefix_weight = 0.42920149;
  double neighborhood_weight = 0.16777838;
  double late_weight = 0.13162124;
  double critical_weight = 0.25815672;
  unsigned budget = 36;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
