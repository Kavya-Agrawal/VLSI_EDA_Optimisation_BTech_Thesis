// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60337078;
  double density_weight = 0.46482268;
  double prefix_weight = 0.28852026;
  double neighborhood_weight = 0.19563670;
  double late_weight = 0.11733431;
  double critical_weight = 0.32084172;
  unsigned budget = 20;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
