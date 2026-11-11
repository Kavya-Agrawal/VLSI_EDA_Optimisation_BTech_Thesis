// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.68631105;
  double density_weight = 0.36801815;
  double prefix_weight = 0.21226176;
  double neighborhood_weight = 0.04733090;
  double late_weight = 0.03434624;
  double critical_weight = 0.23311386;
  unsigned budget = 19;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
