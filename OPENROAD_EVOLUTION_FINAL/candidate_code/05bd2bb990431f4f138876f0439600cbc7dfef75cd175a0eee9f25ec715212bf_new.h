// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92062281;
  double density_weight = 0.52960663;
  double prefix_weight = 0.35061328;
  double neighborhood_weight = 0.12075075;
  double late_weight = 0.27613521;
  double critical_weight = 0.20677787;
  unsigned budget = 14;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
