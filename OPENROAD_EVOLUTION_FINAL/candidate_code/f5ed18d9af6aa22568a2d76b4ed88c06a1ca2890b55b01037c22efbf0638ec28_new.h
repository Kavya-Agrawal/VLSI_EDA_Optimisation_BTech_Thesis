// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76021469;
  double density_weight = 0.52622032;
  double prefix_weight = 0.34989655;
  double neighborhood_weight = 0.21383501;
  double late_weight = 0.16021953;
  double critical_weight = 0.06425323;
  unsigned budget = 40;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
