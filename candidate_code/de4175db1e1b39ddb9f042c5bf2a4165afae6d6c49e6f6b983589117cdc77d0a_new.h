// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15704794;
  double density_weight = 0.11205364;
  double prefix_weight = 0.27890645;
  double neighborhood_weight = 0.16454228;
  double late_weight = 0.21949113;
  double critical_weight = 0.30252144;
  unsigned budget = 37;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
