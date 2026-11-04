// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.28976105;
  double density_weight = 0.26421681;
  double prefix_weight = 0.11055010;
  double neighborhood_weight = 0.18715924;
  double late_weight = 0.23334983;
  double critical_weight = 0.32637467;
  unsigned budget = 33;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
