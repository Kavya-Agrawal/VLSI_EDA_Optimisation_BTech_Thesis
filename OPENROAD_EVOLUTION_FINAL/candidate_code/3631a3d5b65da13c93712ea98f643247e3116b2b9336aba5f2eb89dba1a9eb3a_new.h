// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90494870;
  double density_weight = 0.41818112;
  double prefix_weight = 0.19559986;
  double neighborhood_weight = 0.11141993;
  double late_weight = 0.12171567;
  double critical_weight = 0.46492888;
  unsigned budget = 38;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
