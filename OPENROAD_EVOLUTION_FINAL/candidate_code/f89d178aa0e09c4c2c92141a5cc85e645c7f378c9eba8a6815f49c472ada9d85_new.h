// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96169226;
  double density_weight = 0.12009231;
  double prefix_weight = 0.06166171;
  double neighborhood_weight = 0.00248561;
  double late_weight = 0.28088789;
  double critical_weight = 0.36764294;
  unsigned budget = 33;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
