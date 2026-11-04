// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16231534;
  double density_weight = 0.24588594;
  double prefix_weight = 0.25489001;
  double neighborhood_weight = 0.17849236;
  double late_weight = 0.14822833;
  double critical_weight = 0.39320715;
  unsigned budget = 39;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
