// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.39819323;
  double density_weight = 0.58093288;
  double prefix_weight = 0.29079716;
  double neighborhood_weight = 0.30945627;
  double late_weight = 0.01166914;
  double critical_weight = 0.49988150;
  unsigned budget = 27;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
