// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51760914;
  double density_weight = 0.24061463;
  double prefix_weight = 0.12791991;
  double neighborhood_weight = 0.00219215;
  double late_weight = 0.21240890;
  double critical_weight = 0.15343694;
  unsigned budget = 32;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
