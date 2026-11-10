// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38719607;
  double density_weight = 0.59322204;
  double prefix_weight = 0.10158136;
  double neighborhood_weight = 0.30030954;
  double late_weight = 0.22875672;
  double critical_weight = 0.42081021;
  unsigned budget = 6;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
