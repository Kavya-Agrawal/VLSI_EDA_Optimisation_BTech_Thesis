// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.95455571;
  double density_weight = 0.31766576;
  double prefix_weight = 0.14374404;
  double neighborhood_weight = 0.24744182;
  double late_weight = 0.23968680;
  double critical_weight = 0.16633164;
  unsigned budget = 26;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
