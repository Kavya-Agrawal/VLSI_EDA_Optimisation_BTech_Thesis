// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35991398;
  double density_weight = 0.46391891;
  double prefix_weight = 0.00668412;
  double neighborhood_weight = 0.34541460;
  double late_weight = 0.20554920;
  double critical_weight = 0.31844880;
  unsigned budget = 4;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
