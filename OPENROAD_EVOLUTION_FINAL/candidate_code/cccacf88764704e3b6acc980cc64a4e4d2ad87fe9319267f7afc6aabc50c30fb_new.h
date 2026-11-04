// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76691779;
  double density_weight = 0.05943207;
  double prefix_weight = 0.09648417;
  double neighborhood_weight = 0.09213576;
  double late_weight = 0.18693422;
  double critical_weight = 0.40824511;
  unsigned budget = 23;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
