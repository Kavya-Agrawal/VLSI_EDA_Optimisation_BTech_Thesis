// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12994108;
  double density_weight = 0.13405184;
  double prefix_weight = 0.49595043;
  double neighborhood_weight = 0.09057033;
  double late_weight = 0.06314886;
  double critical_weight = 0.17941938;
  unsigned budget = 22;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
