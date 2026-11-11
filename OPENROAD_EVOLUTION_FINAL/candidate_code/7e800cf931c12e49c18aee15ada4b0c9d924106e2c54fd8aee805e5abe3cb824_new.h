// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61661535;
  double density_weight = 0.04886557;
  double prefix_weight = 0.19641331;
  double neighborhood_weight = 0.26362501;
  double late_weight = 0.08280560;
  double critical_weight = 0.12851144;
  unsigned budget = 23;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
