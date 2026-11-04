// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18220499;
  double density_weight = 0.31784483;
  double prefix_weight = 0.48134268;
  double neighborhood_weight = 0.11702663;
  double late_weight = 0.06383905;
  double critical_weight = 0.00936434;
  unsigned budget = 14;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
