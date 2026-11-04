// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78434869;
  double density_weight = 0.57545556;
  double prefix_weight = 0.31308895;
  double neighborhood_weight = 0.32169837;
  double late_weight = 0.23713388;
  double critical_weight = 0.06845393;
  unsigned budget = 10;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
