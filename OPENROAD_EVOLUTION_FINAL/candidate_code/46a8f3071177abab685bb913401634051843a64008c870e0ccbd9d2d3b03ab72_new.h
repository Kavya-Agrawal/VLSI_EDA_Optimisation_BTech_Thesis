// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46926700;
  double density_weight = 0.06544532;
  double prefix_weight = 0.45311812;
  double neighborhood_weight = 0.01117766;
  double late_weight = 0.27389350;
  double critical_weight = 0.17330525;
  unsigned budget = 24;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
