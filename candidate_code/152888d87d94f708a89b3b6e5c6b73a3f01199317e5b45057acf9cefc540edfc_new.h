// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.69488136;
  double density_weight = 0.00393151;
  double prefix_weight = 0.33976896;
  double neighborhood_weight = 0.30422841;
  double late_weight = 0.07736036;
  double critical_weight = 0.16237149;
  unsigned budget = 30;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
