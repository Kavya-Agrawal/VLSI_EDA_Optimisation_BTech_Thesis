// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66033501;
  double density_weight = 0.53970581;
  double prefix_weight = 0.04368364;
  double neighborhood_weight = 0.32049048;
  double late_weight = 0.01385252;
  double critical_weight = 0.18040062;
  unsigned budget = 29;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
