// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.28912471;
  double density_weight = 0.28272627;
  double prefix_weight = 0.36155643;
  double neighborhood_weight = 0.18352145;
  double late_weight = 0.26853067;
  double critical_weight = 0.22719594;
  unsigned budget = 34;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
