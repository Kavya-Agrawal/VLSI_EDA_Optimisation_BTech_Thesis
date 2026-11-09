// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46744416;
  double density_weight = 0.26709620;
  double prefix_weight = 0.21389084;
  double neighborhood_weight = 0.00558255;
  double late_weight = 0.26260477;
  double critical_weight = 0.17150356;
  unsigned budget = 9;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
