// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48372519;
  double density_weight = 0.57872949;
  double prefix_weight = 0.27148901;
  double neighborhood_weight = 0.39573495;
  double late_weight = 0.27754495;
  double critical_weight = 0.33293316;
  unsigned budget = 17;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
