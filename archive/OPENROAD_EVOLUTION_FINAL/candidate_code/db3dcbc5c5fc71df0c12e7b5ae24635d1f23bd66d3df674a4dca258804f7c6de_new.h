// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61750726;
  double density_weight = 0.56691496;
  double prefix_weight = 0.23946901;
  double neighborhood_weight = 0.24808059;
  double late_weight = 0.20473435;
  double critical_weight = 0.14244204;
  unsigned budget = 23;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
