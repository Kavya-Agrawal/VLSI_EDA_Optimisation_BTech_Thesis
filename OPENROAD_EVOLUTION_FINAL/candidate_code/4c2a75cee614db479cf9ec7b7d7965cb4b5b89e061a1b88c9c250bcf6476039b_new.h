// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72558401;
  double density_weight = 0.54373750;
  double prefix_weight = 0.48088202;
  double neighborhood_weight = 0.08974091;
  double late_weight = 0.22747087;
  double critical_weight = 0.38865714;
  unsigned budget = 34;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
