// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.77176640;
  double density_weight = 0.23432301;
  double prefix_weight = 0.14771955;
  double neighborhood_weight = 0.19037726;
  double late_weight = 0.04907946;
  double critical_weight = 0.45936108;
  unsigned budget = 24;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
