// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51036135;
  double density_weight = 0.09000289;
  double prefix_weight = 0.38456240;
  double neighborhood_weight = 0.27818665;
  double late_weight = 0.25534284;
  double critical_weight = 0.30797296;
  unsigned budget = 14;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
