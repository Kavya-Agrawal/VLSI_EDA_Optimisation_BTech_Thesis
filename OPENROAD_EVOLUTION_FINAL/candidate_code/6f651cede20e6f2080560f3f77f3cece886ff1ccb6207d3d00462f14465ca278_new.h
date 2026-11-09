// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86314976;
  double density_weight = 0.15790129;
  double prefix_weight = 0.31999136;
  double neighborhood_weight = 0.29645496;
  double late_weight = 0.24708284;
  double critical_weight = 0.07660342;
  unsigned budget = 16;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
