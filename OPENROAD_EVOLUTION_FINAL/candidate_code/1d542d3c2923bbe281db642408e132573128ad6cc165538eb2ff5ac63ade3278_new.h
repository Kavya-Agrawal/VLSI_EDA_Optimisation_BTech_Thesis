// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12713285;
  double density_weight = 0.39080624;
  double prefix_weight = 0.38821722;
  double neighborhood_weight = 0.25874861;
  double late_weight = 0.04768942;
  double critical_weight = 0.16186692;
  unsigned budget = 36;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
