// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70738946;
  double density_weight = 0.06826608;
  double prefix_weight = 0.31980668;
  double neighborhood_weight = 0.27969895;
  double late_weight = 0.09147204;
  double critical_weight = 0.18738713;
  unsigned budget = 27;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
