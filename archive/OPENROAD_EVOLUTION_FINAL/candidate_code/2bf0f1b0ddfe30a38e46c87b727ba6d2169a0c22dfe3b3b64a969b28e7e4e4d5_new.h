// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.32339794;
  double density_weight = 0.51575674;
  double prefix_weight = 0.03672274;
  double neighborhood_weight = 0.04014638;
  double late_weight = 0.03273364;
  double critical_weight = 0.43228441;
  unsigned budget = 8;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
