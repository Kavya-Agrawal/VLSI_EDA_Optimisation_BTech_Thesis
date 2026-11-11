// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58591325;
  double density_weight = 0.39313640;
  double prefix_weight = 0.17672362;
  double neighborhood_weight = 0.01977667;
  double late_weight = 0.15934730;
  double critical_weight = 0.47193880;
  unsigned budget = 13;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
