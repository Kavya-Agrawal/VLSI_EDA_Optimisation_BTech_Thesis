// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52004699;
  double density_weight = 0.53127444;
  double prefix_weight = 0.27018015;
  double neighborhood_weight = 0.01142621;
  double late_weight = 0.24083790;
  double critical_weight = 0.08021772;
  unsigned budget = 31;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
