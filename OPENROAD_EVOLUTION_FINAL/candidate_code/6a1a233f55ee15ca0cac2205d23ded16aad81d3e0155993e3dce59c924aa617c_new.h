// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24044609;
  double density_weight = 0.20318842;
  double prefix_weight = 0.45779497;
  double neighborhood_weight = 0.34686515;
  double late_weight = 0.22956552;
  double critical_weight = 0.24523200;
  unsigned budget = 26;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
