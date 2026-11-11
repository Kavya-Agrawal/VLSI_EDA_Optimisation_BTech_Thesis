// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76852880;
  double density_weight = 0.39926943;
  double prefix_weight = 0.23689602;
  double neighborhood_weight = 0.11573455;
  double late_weight = 0.02006036;
  double critical_weight = 0.25292693;
  unsigned budget = 21;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
