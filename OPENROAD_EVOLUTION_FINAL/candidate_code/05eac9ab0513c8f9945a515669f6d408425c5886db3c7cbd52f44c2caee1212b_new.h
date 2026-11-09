// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12863815;
  double density_weight = 0.36808082;
  double prefix_weight = 0.01342717;
  double neighborhood_weight = 0.22521056;
  double late_weight = 0.29528774;
  double critical_weight = 0.12587953;
  unsigned budget = 19;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
