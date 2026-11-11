// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55681728;
  double density_weight = 0.04505222;
  double prefix_weight = 0.10593131;
  double neighborhood_weight = 0.23847385;
  double late_weight = 0.10713958;
  double critical_weight = 0.06317508;
  unsigned budget = 21;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
