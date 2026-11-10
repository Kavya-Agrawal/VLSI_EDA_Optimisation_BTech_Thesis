// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21274007;
  double density_weight = 0.37492502;
  double prefix_weight = 0.05743070;
  double neighborhood_weight = 0.07122105;
  double late_weight = 0.11427438;
  double critical_weight = 0.06249612;
  unsigned budget = 29;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
