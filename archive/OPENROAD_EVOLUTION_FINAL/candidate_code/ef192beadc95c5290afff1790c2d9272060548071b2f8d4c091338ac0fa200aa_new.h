// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16632838;
  double density_weight = 0.44352028;
  double prefix_weight = 0.40037908;
  double neighborhood_weight = 0.20867738;
  double late_weight = 0.00013265;
  double critical_weight = 0.09834268;
  unsigned budget = 6;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
