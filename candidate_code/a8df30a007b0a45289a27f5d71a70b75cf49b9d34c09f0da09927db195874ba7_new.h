// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34091694;
  double density_weight = 0.05896706;
  double prefix_weight = 0.14813634;
  double neighborhood_weight = 0.14045808;
  double late_weight = 0.07544566;
  double critical_weight = 0.08584722;
  unsigned budget = 10;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
