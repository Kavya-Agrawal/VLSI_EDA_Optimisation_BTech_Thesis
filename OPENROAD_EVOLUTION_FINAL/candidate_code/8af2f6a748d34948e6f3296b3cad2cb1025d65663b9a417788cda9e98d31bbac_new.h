// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88078741;
  double density_weight = 0.43524021;
  double prefix_weight = 0.49292917;
  double neighborhood_weight = 0.24202693;
  double late_weight = 0.00188409;
  double critical_weight = 0.01064452;
  unsigned budget = 20;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
