// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73064430;
  double density_weight = 0.18203319;
  double prefix_weight = 0.36527087;
  double neighborhood_weight = 0.32643662;
  double late_weight = 0.08406467;
  double critical_weight = 0.01356511;
  unsigned budget = 5;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
