// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70597797;
  double density_weight = 0.42774047;
  double prefix_weight = 0.02672785;
  double neighborhood_weight = 0.04859095;
  double late_weight = 0.23227492;
  double critical_weight = 0.18650625;
  unsigned budget = 8;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
