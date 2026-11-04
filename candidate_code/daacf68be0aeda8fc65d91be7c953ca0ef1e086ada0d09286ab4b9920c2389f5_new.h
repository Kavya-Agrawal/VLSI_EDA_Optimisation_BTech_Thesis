// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13400096;
  double density_weight = 0.46391885;
  double prefix_weight = 0.12040023;
  double neighborhood_weight = 0.23096443;
  double late_weight = 0.05969273;
  double critical_weight = 0.28145102;
  unsigned budget = 15;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
