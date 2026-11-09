// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19970109;
  double density_weight = 0.20192754;
  double prefix_weight = 0.12910533;
  double neighborhood_weight = 0.22754232;
  double late_weight = 0.26670886;
  double critical_weight = 0.21203832;
  unsigned budget = 22;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
