// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24430086;
  double density_weight = 0.32172244;
  double prefix_weight = 0.17451511;
  double neighborhood_weight = 0.08562668;
  double late_weight = 0.17533726;
  double critical_weight = 0.10274531;
  unsigned budget = 35;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
