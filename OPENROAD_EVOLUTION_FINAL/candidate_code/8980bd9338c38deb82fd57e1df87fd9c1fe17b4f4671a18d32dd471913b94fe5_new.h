// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.28566070;
  double density_weight = 0.35960513;
  double prefix_weight = 0.28203409;
  double neighborhood_weight = 0.03120089;
  double late_weight = 0.23084412;
  double critical_weight = 0.46288513;
  unsigned budget = 25;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
