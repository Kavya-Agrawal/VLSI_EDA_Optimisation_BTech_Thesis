// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.49022216;
  double density_weight = 0.51170601;
  double prefix_weight = 0.34112130;
  double neighborhood_weight = 0.10098900;
  double late_weight = 0.24638406;
  double critical_weight = 0.44315958;
  unsigned budget = 30;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
