// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94891819;
  double density_weight = 0.45136690;
  double prefix_weight = 0.03316826;
  double neighborhood_weight = 0.15035162;
  double late_weight = 0.05258279;
  double critical_weight = 0.31958342;
  unsigned budget = 18;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
