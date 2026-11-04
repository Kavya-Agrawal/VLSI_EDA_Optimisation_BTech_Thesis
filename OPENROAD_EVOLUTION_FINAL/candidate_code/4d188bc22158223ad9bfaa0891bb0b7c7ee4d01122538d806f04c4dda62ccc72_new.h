// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18549006;
  double density_weight = 0.00315662;
  double prefix_weight = 0.37820715;
  double neighborhood_weight = 0.26356661;
  double late_weight = 0.06158620;
  double critical_weight = 0.39458094;
  unsigned budget = 11;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
