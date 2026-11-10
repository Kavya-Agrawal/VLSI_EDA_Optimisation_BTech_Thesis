// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.26223203;
  double density_weight = 0.00452968;
  double prefix_weight = 0.16687566;
  double neighborhood_weight = 0.07651865;
  double late_weight = 0.07273837;
  double critical_weight = 0.39582776;
  unsigned budget = 35;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
