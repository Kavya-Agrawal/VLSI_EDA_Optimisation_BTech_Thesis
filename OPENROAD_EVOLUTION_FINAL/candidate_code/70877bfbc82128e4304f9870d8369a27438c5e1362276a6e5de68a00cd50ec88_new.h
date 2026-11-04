// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20985950;
  double density_weight = 0.10145080;
  double prefix_weight = 0.30445245;
  double neighborhood_weight = 0.23011329;
  double late_weight = 0.11590671;
  double critical_weight = 0.39043642;
  unsigned budget = 19;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
