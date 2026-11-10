// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73674678;
  double density_weight = 0.21797922;
  double prefix_weight = 0.01304826;
  double neighborhood_weight = 0.13040224;
  double late_weight = 0.04950499;
  double critical_weight = 0.04699468;
  unsigned budget = 38;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
