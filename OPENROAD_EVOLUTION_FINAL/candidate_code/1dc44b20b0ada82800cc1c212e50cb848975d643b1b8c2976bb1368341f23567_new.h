// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14125975;
  double density_weight = 0.30585555;
  double prefix_weight = 0.07191042;
  double neighborhood_weight = 0.02116048;
  double late_weight = 0.00403592;
  double critical_weight = 0.42429702;
  unsigned budget = 36;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
