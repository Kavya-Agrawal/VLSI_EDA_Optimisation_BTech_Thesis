// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30646006;
  double density_weight = 0.04271561;
  double prefix_weight = 0.12246706;
  double neighborhood_weight = 0.14876823;
  double late_weight = 0.23712494;
  double critical_weight = 0.01879214;
  unsigned budget = 35;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
