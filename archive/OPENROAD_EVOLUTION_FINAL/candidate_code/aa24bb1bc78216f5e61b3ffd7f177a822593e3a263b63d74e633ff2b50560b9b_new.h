// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07684082;
  double density_weight = 0.35939921;
  double prefix_weight = 0.10708817;
  double neighborhood_weight = 0.09748531;
  double late_weight = 0.28752304;
  double critical_weight = 0.03326512;
  unsigned budget = 25;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
