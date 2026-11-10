// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55594054;
  double density_weight = 0.21868366;
  double prefix_weight = 0.35045113;
  double neighborhood_weight = 0.37471871;
  double late_weight = 0.07771544;
  double critical_weight = 0.38869908;
  unsigned budget = 37;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
