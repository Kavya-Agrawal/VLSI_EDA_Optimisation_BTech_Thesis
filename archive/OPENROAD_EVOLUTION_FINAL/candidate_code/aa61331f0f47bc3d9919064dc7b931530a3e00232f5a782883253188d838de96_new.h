// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43307182;
  double density_weight = 0.16744752;
  double prefix_weight = 0.19591662;
  double neighborhood_weight = 0.19086654;
  double late_weight = 0.04086606;
  double critical_weight = 0.11478937;
  unsigned budget = 11;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
