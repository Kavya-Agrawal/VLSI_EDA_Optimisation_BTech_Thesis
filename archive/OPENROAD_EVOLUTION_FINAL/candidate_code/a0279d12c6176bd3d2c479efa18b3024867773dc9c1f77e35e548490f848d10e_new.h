// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70177237;
  double density_weight = 0.24906978;
  double prefix_weight = 0.20770180;
  double neighborhood_weight = 0.07297413;
  double late_weight = 0.14132126;
  double critical_weight = 0.21785377;
  unsigned budget = 28;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
