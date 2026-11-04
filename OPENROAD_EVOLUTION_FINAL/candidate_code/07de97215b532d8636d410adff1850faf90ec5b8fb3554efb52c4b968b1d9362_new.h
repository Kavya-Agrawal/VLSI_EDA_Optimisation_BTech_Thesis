// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16185294;
  double density_weight = 0.11489631;
  double prefix_weight = 0.17302256;
  double neighborhood_weight = 0.27165709;
  double late_weight = 0.02759404;
  double critical_weight = 0.32085249;
  unsigned budget = 22;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
