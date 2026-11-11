// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82079988;
  double density_weight = 0.07793858;
  double prefix_weight = 0.18322788;
  double neighborhood_weight = 0.22799502;
  double late_weight = 0.00022892;
  double critical_weight = 0.48738991;
  unsigned budget = 20;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
