// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21112167;
  double density_weight = 0.26912107;
  double prefix_weight = 0.12952273;
  double neighborhood_weight = 0.38802064;
  double late_weight = 0.09863593;
  double critical_weight = 0.11665051;
  unsigned budget = 8;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
