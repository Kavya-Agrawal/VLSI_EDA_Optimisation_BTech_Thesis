// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35793338;
  double density_weight = 0.07390312;
  double prefix_weight = 0.47408168;
  double neighborhood_weight = 0.28418977;
  double late_weight = 0.18062827;
  double critical_weight = 0.29669297;
  unsigned budget = 31;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
