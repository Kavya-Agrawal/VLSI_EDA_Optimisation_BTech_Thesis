// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94040718;
  double density_weight = 0.59937364;
  double prefix_weight = 0.28108467;
  double neighborhood_weight = 0.17649965;
  double late_weight = 0.21081305;
  double critical_weight = 0.16104487;
  unsigned budget = 33;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
