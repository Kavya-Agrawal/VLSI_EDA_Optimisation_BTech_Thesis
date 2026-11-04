// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71121747;
  double density_weight = 0.30345495;
  double prefix_weight = 0.10130648;
  double neighborhood_weight = 0.12490266;
  double late_weight = 0.12079171;
  double critical_weight = 0.21591919;
  unsigned budget = 30;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
