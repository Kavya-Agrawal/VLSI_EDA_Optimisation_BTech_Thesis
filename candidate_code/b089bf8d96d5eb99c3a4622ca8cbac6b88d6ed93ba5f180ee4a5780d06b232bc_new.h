// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18130579;
  double density_weight = 0.05792609;
  double prefix_weight = 0.41482861;
  double neighborhood_weight = 0.11008919;
  double late_weight = 0.10834752;
  double critical_weight = 0.02422287;
  unsigned budget = 21;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
