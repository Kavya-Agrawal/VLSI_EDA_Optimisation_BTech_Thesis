// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.39620948;
  double density_weight = 0.02772599;
  double prefix_weight = 0.23663647;
  double neighborhood_weight = 0.06584813;
  double late_weight = 0.09140525;
  double critical_weight = 0.16413429;
  unsigned budget = 10;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
