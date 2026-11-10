// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09331145;
  double density_weight = 0.21133536;
  double prefix_weight = 0.10182738;
  double neighborhood_weight = 0.04603226;
  double late_weight = 0.10844103;
  double critical_weight = 0.17493061;
  unsigned budget = 20;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
