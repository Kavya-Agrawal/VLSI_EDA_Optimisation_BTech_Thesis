// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60353885;
  double density_weight = 0.42680387;
  double prefix_weight = 0.38010947;
  double neighborhood_weight = 0.31266829;
  double late_weight = 0.15044296;
  double critical_weight = 0.01699050;
  unsigned budget = 29;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
