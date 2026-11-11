// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.39854076;
  double density_weight = 0.57251806;
  double prefix_weight = 0.04020287;
  double neighborhood_weight = 0.28341115;
  double late_weight = 0.17000359;
  double critical_weight = 0.37608273;
  unsigned budget = 6;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
