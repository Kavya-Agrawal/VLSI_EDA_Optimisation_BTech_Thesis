// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93520996;
  double density_weight = 0.32940515;
  double prefix_weight = 0.06727296;
  double neighborhood_weight = 0.22638192;
  double late_weight = 0.22869621;
  double critical_weight = 0.18656518;
  unsigned budget = 40;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
