// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51488992;
  double density_weight = 0.22159606;
  double prefix_weight = 0.20487689;
  double neighborhood_weight = 0.38697545;
  double late_weight = 0.15539960;
  double critical_weight = 0.18905581;
  unsigned budget = 21;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
