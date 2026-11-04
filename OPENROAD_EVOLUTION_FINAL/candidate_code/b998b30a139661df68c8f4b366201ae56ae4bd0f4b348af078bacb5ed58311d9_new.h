// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30700264;
  double density_weight = 0.48230898;
  double prefix_weight = 0.20761024;
  double neighborhood_weight = 0.32511113;
  double late_weight = 0.12911329;
  double critical_weight = 0.38237886;
  unsigned budget = 13;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
