// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43705122;
  double density_weight = 0.17109995;
  double prefix_weight = 0.32140207;
  double neighborhood_weight = 0.10206010;
  double late_weight = 0.14298274;
  double critical_weight = 0.38180985;
  unsigned budget = 26;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
