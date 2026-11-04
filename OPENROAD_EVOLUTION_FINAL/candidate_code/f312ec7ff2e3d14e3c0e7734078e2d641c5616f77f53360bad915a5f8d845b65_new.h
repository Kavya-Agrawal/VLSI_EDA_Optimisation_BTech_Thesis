// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.77836533;
  double density_weight = 0.41905516;
  double prefix_weight = 0.24171411;
  double neighborhood_weight = 0.10631436;
  double late_weight = 0.08974976;
  double critical_weight = 0.16535522;
  unsigned budget = 20;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
