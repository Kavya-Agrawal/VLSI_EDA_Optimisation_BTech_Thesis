// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96683212;
  double density_weight = 0.30261956;
  double prefix_weight = 0.16926969;
  double neighborhood_weight = 0.15779238;
  double late_weight = 0.20544916;
  double critical_weight = 0.10200842;
  unsigned budget = 24;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
