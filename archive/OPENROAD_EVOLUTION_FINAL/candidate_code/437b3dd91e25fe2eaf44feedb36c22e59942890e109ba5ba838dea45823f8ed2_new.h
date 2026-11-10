// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85077664;
  double density_weight = 0.15204889;
  double prefix_weight = 0.02527654;
  double neighborhood_weight = 0.32854011;
  double late_weight = 0.27342519;
  double critical_weight = 0.43078017;
  unsigned budget = 14;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
