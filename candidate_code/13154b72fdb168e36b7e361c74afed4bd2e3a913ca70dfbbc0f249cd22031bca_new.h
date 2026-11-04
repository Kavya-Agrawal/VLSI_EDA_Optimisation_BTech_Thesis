// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15167087;
  double density_weight = 0.39505012;
  double prefix_weight = 0.45480880;
  double neighborhood_weight = 0.12445509;
  double late_weight = 0.01409229;
  double critical_weight = 0.36555026;
  unsigned budget = 14;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
