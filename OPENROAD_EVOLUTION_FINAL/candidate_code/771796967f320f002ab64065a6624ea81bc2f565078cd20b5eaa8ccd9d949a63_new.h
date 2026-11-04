// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20580370;
  double density_weight = 0.08364819;
  double prefix_weight = 0.49226557;
  double neighborhood_weight = 0.21461770;
  double late_weight = 0.15814813;
  double critical_weight = 0.14998665;
  unsigned budget = 30;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
