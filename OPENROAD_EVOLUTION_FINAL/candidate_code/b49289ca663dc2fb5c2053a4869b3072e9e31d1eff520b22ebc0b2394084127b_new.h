// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.77476544;
  double density_weight = 0.18172089;
  double prefix_weight = 0.29447606;
  double neighborhood_weight = 0.20601070;
  double late_weight = 0.16518783;
  double critical_weight = 0.28680069;
  unsigned budget = 31;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
