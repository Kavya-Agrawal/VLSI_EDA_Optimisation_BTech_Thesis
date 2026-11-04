// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60900667;
  double density_weight = 0.05694861;
  double prefix_weight = 0.05952455;
  double neighborhood_weight = 0.25974182;
  double late_weight = 0.11772834;
  double critical_weight = 0.13627826;
  unsigned budget = 16;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
