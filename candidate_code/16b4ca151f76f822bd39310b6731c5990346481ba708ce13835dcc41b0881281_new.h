// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02509951;
  double density_weight = 0.09838451;
  double prefix_weight = 0.08784966;
  double neighborhood_weight = 0.26781172;
  double late_weight = 0.16463213;
  double critical_weight = 0.30346437;
  unsigned budget = 12;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
