// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31077949;
  double density_weight = 0.12946571;
  double prefix_weight = 0.27546824;
  double neighborhood_weight = 0.17737809;
  double late_weight = 0.02032093;
  double critical_weight = 0.22326539;
  unsigned budget = 11;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
