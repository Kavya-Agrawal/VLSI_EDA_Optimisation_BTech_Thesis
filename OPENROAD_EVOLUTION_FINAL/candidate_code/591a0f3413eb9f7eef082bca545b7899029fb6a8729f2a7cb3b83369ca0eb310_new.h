// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54278399;
  double density_weight = 0.13044385;
  double prefix_weight = 0.44100742;
  double neighborhood_weight = 0.35116073;
  double late_weight = 0.16308952;
  double critical_weight = 0.44829858;
  unsigned budget = 24;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
