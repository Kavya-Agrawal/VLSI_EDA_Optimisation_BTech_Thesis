// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76130545;
  double density_weight = 0.06141481;
  double prefix_weight = 0.19410848;
  double neighborhood_weight = 0.27169598;
  double late_weight = 0.25602094;
  double critical_weight = 0.16384697;
  unsigned budget = 8;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
