// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60139935;
  double density_weight = 0.44552930;
  double prefix_weight = 0.31866719;
  double neighborhood_weight = 0.11040898;
  double late_weight = 0.00337476;
  double critical_weight = 0.29029529;
  unsigned budget = 15;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
