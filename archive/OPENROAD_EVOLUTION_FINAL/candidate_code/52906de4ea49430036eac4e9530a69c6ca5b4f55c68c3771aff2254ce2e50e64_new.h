// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36232658;
  double density_weight = 0.35809289;
  double prefix_weight = 0.21802907;
  double neighborhood_weight = 0.33278134;
  double late_weight = 0.25894841;
  double critical_weight = 0.43680321;
  unsigned budget = 15;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
