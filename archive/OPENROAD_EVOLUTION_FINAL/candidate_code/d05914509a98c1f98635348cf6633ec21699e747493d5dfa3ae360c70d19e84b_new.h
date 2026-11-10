// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24359756;
  double density_weight = 0.55044664;
  double prefix_weight = 0.23823552;
  double neighborhood_weight = 0.24301511;
  double late_weight = 0.19464804;
  double critical_weight = 0.40182192;
  unsigned budget = 10;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
