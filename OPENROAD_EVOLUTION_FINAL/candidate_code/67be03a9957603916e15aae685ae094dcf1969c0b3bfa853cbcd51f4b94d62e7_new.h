// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45708007;
  double density_weight = 0.21116529;
  double prefix_weight = 0.22985000;
  double neighborhood_weight = 0.34035542;
  double late_weight = 0.11545194;
  double critical_weight = 0.44345808;
  unsigned budget = 37;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
