// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16391889;
  double density_weight = 0.20198942;
  double prefix_weight = 0.10098906;
  double neighborhood_weight = 0.00991282;
  double late_weight = 0.01150737;
  double critical_weight = 0.04778545;
  unsigned budget = 28;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
