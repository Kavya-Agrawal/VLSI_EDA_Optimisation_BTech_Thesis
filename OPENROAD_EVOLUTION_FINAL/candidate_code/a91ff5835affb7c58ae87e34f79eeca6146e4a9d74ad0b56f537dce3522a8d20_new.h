// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37948028;
  double density_weight = 0.25998052;
  double prefix_weight = 0.22176630;
  double neighborhood_weight = 0.29515605;
  double late_weight = 0.17303064;
  double critical_weight = 0.48339909;
  unsigned budget = 13;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
