// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.11458365;
  double density_weight = 0.16918439;
  double prefix_weight = 0.46496676;
  double neighborhood_weight = 0.16598300;
  double late_weight = 0.23149497;
  double critical_weight = 0.21842101;
  unsigned budget = 32;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
