// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30670208;
  double density_weight = 0.00989911;
  double prefix_weight = 0.43251651;
  double neighborhood_weight = 0.14283438;
  double late_weight = 0.18136971;
  double critical_weight = 0.35998515;
  unsigned budget = 27;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
