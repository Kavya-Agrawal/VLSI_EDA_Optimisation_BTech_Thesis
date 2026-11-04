// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58637875;
  double density_weight = 0.14056353;
  double prefix_weight = 0.40525346;
  double neighborhood_weight = 0.28936125;
  double late_weight = 0.22741436;
  double critical_weight = 0.27968194;
  unsigned budget = 22;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
