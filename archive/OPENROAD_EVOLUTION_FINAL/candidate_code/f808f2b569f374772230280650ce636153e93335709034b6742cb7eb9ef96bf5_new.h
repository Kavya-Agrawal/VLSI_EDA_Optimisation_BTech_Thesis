// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65539037;
  double density_weight = 0.33361400;
  double prefix_weight = 0.01449851;
  double neighborhood_weight = 0.30962225;
  double late_weight = 0.04093363;
  double critical_weight = 0.21083159;
  unsigned budget = 31;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
