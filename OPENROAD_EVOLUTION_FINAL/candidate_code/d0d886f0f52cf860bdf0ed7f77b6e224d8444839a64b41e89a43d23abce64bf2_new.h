// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51878640;
  double density_weight = 0.44412684;
  double prefix_weight = 0.09246536;
  double neighborhood_weight = 0.33240943;
  double late_weight = 0.18568016;
  double critical_weight = 0.37761782;
  unsigned budget = 40;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
