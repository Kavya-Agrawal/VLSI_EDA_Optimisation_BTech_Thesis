// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44365696;
  double density_weight = 0.56346037;
  double prefix_weight = 0.26950928;
  double neighborhood_weight = 0.36758680;
  double late_weight = 0.15277392;
  double critical_weight = 0.40830841;
  unsigned budget = 26;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
