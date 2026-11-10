// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52125650;
  double density_weight = 0.03281599;
  double prefix_weight = 0.00686897;
  double neighborhood_weight = 0.15531395;
  double late_weight = 0.03996978;
  double critical_weight = 0.47047730;
  unsigned budget = 17;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
