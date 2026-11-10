// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.50605821;
  double density_weight = 0.02123081;
  double prefix_weight = 0.24980753;
  double neighborhood_weight = 0.18031955;
  double late_weight = 0.14453402;
  double critical_weight = 0.01805074;
  unsigned budget = 27;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
