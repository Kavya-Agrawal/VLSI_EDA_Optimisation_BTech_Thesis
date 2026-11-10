// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.68100665;
  double density_weight = 0.19436597;
  double prefix_weight = 0.44320709;
  double neighborhood_weight = 0.16109302;
  double late_weight = 0.19163267;
  double critical_weight = 0.11778111;
  unsigned budget = 17;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
