// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43067434;
  double density_weight = 0.16702262;
  double prefix_weight = 0.26177233;
  double neighborhood_weight = 0.00055233;
  double late_weight = 0.15891413;
  double critical_weight = 0.19654244;
  unsigned budget = 32;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
