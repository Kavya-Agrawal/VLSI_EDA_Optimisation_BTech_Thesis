// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78454057;
  double density_weight = 0.11551663;
  double prefix_weight = 0.39599781;
  double neighborhood_weight = 0.35595506;
  double late_weight = 0.03426306;
  double critical_weight = 0.13592527;
  unsigned budget = 29;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
