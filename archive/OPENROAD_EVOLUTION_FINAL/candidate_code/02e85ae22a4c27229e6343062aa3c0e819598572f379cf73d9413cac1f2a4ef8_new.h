// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.42240864;
  double density_weight = 0.17671644;
  double prefix_weight = 0.38273160;
  double neighborhood_weight = 0.08432579;
  double late_weight = 0.04966636;
  double critical_weight = 0.22591838;
  unsigned budget = 6;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
