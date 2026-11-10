// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64974967;
  double density_weight = 0.04662587;
  double prefix_weight = 0.00976630;
  double neighborhood_weight = 0.28690961;
  double late_weight = 0.26119587;
  double critical_weight = 0.36651780;
  unsigned budget = 9;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
