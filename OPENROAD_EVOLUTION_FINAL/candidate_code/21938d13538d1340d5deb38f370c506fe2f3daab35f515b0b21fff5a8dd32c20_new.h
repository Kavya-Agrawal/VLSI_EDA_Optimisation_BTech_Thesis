// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74448051;
  double density_weight = 0.02137977;
  double prefix_weight = 0.09773900;
  double neighborhood_weight = 0.39610694;
  double late_weight = 0.20251280;
  double critical_weight = 0.28045554;
  unsigned budget = 24;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
