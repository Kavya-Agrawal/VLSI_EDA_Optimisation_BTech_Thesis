// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43508790;
  double density_weight = 0.32715796;
  double prefix_weight = 0.15012427;
  double neighborhood_weight = 0.23722426;
  double late_weight = 0.21916311;
  double critical_weight = 0.48313561;
  unsigned budget = 15;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
