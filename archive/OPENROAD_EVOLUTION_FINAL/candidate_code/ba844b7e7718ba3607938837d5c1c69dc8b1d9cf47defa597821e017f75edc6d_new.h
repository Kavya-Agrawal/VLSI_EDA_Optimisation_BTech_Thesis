// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48642123;
  double density_weight = 0.34026093;
  double prefix_weight = 0.26279748;
  double neighborhood_weight = 0.38410214;
  double late_weight = 0.14156838;
  double critical_weight = 0.47556047;
  unsigned budget = 29;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
