// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35416251;
  double density_weight = 0.15097810;
  double prefix_weight = 0.25139775;
  double neighborhood_weight = 0.39451544;
  double late_weight = 0.07487335;
  double critical_weight = 0.34114843;
  unsigned budget = 19;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
