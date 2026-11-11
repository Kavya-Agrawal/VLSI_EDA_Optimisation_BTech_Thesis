// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.05075136;
  double density_weight = 0.29626364;
  double prefix_weight = 0.00310779;
  double neighborhood_weight = 0.32843104;
  double late_weight = 0.23126918;
  double critical_weight = 0.43987893;
  unsigned budget = 7;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
