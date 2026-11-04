// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.77952176;
  double density_weight = 0.44465112;
  double prefix_weight = 0.19517616;
  double neighborhood_weight = 0.31370204;
  double late_weight = 0.20686615;
  double critical_weight = 0.17203321;
  unsigned budget = 36;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
