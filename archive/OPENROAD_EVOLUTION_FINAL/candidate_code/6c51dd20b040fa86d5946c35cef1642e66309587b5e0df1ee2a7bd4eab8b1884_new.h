// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84847065;
  double density_weight = 0.56530669;
  double prefix_weight = 0.39716093;
  double neighborhood_weight = 0.17427974;
  double late_weight = 0.06787459;
  double critical_weight = 0.42690859;
  unsigned budget = 31;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
