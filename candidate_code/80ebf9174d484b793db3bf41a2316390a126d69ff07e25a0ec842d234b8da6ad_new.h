// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04798702;
  double density_weight = 0.05074792;
  double prefix_weight = 0.07302283;
  double neighborhood_weight = 0.29722633;
  double late_weight = 0.27172312;
  double critical_weight = 0.49351488;
  unsigned budget = 27;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
