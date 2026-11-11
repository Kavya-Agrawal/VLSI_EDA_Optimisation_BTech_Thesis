// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23508954;
  double density_weight = 0.37605136;
  double prefix_weight = 0.14145145;
  double neighborhood_weight = 0.09625458;
  double late_weight = 0.14326973;
  double critical_weight = 0.28219321;
  unsigned budget = 23;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
