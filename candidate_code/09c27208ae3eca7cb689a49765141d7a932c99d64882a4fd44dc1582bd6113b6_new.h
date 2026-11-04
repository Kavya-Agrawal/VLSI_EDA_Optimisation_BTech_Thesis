// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45859010;
  double density_weight = 0.57856996;
  double prefix_weight = 0.47186851;
  double neighborhood_weight = 0.30549017;
  double late_weight = 0.04508836;
  double critical_weight = 0.39696124;
  unsigned budget = 11;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
