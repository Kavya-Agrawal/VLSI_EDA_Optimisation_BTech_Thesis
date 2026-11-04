// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47823686;
  double density_weight = 0.29196072;
  double prefix_weight = 0.06406172;
  double neighborhood_weight = 0.20568657;
  double late_weight = 0.05891062;
  double critical_weight = 0.22161238;
  unsigned budget = 31;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
