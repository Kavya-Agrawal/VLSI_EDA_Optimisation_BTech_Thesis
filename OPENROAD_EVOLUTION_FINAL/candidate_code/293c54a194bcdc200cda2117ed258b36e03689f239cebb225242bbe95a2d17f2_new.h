// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66354818;
  double density_weight = 0.41046336;
  double prefix_weight = 0.29149843;
  double neighborhood_weight = 0.06398928;
  double late_weight = 0.13180394;
  double critical_weight = 0.35087293;
  unsigned budget = 15;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
