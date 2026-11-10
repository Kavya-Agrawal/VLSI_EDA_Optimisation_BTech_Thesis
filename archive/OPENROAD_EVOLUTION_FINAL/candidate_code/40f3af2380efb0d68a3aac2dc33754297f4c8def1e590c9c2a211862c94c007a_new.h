// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10482361;
  double density_weight = 0.09760851;
  double prefix_weight = 0.43583091;
  double neighborhood_weight = 0.12222564;
  double late_weight = 0.22866857;
  double critical_weight = 0.07277607;
  unsigned budget = 34;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
