// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20491050;
  double density_weight = 0.54983011;
  double prefix_weight = 0.30737901;
  double neighborhood_weight = 0.03027417;
  double late_weight = 0.10098401;
  double critical_weight = 0.41837886;
  unsigned budget = 28;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
