// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58670447;
  double density_weight = 0.59751356;
  double prefix_weight = 0.26225677;
  double neighborhood_weight = 0.29569048;
  double late_weight = 0.09331521;
  double critical_weight = 0.09895445;
  unsigned budget = 20;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
