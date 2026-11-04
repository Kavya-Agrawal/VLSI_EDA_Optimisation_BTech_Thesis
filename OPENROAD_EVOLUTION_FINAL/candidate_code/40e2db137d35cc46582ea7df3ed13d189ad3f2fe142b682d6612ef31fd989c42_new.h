// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60013626;
  double density_weight = 0.02186722;
  double prefix_weight = 0.21639483;
  double neighborhood_weight = 0.34760490;
  double late_weight = 0.21590954;
  double critical_weight = 0.35230795;
  unsigned budget = 8;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
