// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.05298412;
  double density_weight = 0.01914000;
  double prefix_weight = 0.16756248;
  double neighborhood_weight = 0.27377730;
  double late_weight = 0.03951783;
  double critical_weight = 0.00437688;
  unsigned budget = 34;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
