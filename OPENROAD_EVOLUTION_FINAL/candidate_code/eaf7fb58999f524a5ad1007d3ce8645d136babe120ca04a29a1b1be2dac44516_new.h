// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16947159;
  double density_weight = 0.22339365;
  double prefix_weight = 0.09457449;
  double neighborhood_weight = 0.20528220;
  double late_weight = 0.00038784;
  double critical_weight = 0.31443059;
  unsigned budget = 28;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
