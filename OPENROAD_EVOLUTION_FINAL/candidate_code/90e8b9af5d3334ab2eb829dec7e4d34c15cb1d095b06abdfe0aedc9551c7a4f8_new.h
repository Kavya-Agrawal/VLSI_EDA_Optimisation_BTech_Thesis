// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41988765;
  double density_weight = 0.48647614;
  double prefix_weight = 0.30292991;
  double neighborhood_weight = 0.09623827;
  double late_weight = 0.29567095;
  double critical_weight = 0.23414980;
  unsigned budget = 16;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
