// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.95107842;
  double density_weight = 0.38099756;
  double prefix_weight = 0.05360433;
  double neighborhood_weight = 0.35278544;
  double late_weight = 0.21612745;
  double critical_weight = 0.23948707;
  unsigned budget = 12;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
