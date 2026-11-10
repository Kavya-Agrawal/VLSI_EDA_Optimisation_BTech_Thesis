// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24563688;
  double density_weight = 0.51194203;
  double prefix_weight = 0.39736236;
  double neighborhood_weight = 0.12656440;
  double late_weight = 0.02740448;
  double critical_weight = 0.24189352;
  unsigned budget = 31;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
