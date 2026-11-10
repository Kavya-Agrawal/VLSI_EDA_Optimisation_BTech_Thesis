// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55195354;
  double density_weight = 0.28878227;
  double prefix_weight = 0.37585078;
  double neighborhood_weight = 0.29797730;
  double late_weight = 0.18762080;
  double critical_weight = 0.08299553;
  unsigned budget = 33;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
