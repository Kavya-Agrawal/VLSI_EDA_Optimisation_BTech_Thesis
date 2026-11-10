// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20682515;
  double density_weight = 0.39105771;
  double prefix_weight = 0.40384634;
  double neighborhood_weight = 0.22108210;
  double late_weight = 0.07745164;
  double critical_weight = 0.18822475;
  unsigned budget = 16;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
