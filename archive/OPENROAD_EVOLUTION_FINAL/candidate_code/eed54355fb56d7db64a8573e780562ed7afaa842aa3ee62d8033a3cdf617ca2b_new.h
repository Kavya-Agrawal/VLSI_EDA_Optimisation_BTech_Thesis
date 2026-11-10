// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03758324;
  double density_weight = 0.45827291;
  double prefix_weight = 0.26238377;
  double neighborhood_weight = 0.19721931;
  double late_weight = 0.01076364;
  double critical_weight = 0.08687958;
  unsigned budget = 35;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
