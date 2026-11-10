// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58915884;
  double density_weight = 0.03467390;
  double prefix_weight = 0.10024562;
  double neighborhood_weight = 0.02562965;
  double late_weight = 0.00868723;
  double critical_weight = 0.21426579;
  unsigned budget = 30;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
