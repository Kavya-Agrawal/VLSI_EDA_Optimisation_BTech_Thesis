// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79832966;
  double density_weight = 0.34268117;
  double prefix_weight = 0.36111328;
  double neighborhood_weight = 0.12687016;
  double late_weight = 0.00195737;
  double critical_weight = 0.32492955;
  unsigned budget = 20;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
