// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74321432;
  double density_weight = 0.01043511;
  double prefix_weight = 0.30127645;
  double neighborhood_weight = 0.18841244;
  double late_weight = 0.09853560;
  double critical_weight = 0.42118836;
  unsigned budget = 35;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
