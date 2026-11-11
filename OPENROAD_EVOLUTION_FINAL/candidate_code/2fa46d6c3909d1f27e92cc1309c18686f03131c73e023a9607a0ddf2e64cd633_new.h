// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16796949;
  double density_weight = 0.31388629;
  double prefix_weight = 0.42093919;
  double neighborhood_weight = 0.28884421;
  double late_weight = 0.01320205;
  double critical_weight = 0.10120085;
  unsigned budget = 4;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
