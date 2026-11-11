// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.35241942;
  double density_weight = 0.42108114;
  double prefix_weight = 0.17196979;
  double neighborhood_weight = 0.12314305;
  double late_weight = 0.06243073;
  double critical_weight = 0.38457470;
  unsigned budget = 6;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
