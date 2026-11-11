// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.08163582;
  double density_weight = 0.12625289;
  double prefix_weight = 0.36489631;
  double neighborhood_weight = 0.35506470;
  double late_weight = 0.14006836;
  double critical_weight = 0.12195746;
  unsigned budget = 7;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
