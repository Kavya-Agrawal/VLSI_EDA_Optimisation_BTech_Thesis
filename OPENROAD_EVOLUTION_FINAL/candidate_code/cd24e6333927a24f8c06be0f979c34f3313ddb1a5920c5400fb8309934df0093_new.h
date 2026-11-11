// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.68636057;
  double density_weight = 0.48022508;
  double prefix_weight = 0.36639544;
  double neighborhood_weight = 0.08918802;
  double late_weight = 0.29992272;
  double critical_weight = 0.15498002;
  unsigned budget = 21;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
