// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62347653;
  double density_weight = 0.06740938;
  double prefix_weight = 0.18677133;
  double neighborhood_weight = 0.28256518;
  double late_weight = 0.21154429;
  double critical_weight = 0.34019764;
  unsigned budget = 35;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
