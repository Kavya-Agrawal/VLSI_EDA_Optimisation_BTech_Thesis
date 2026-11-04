// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73087766;
  double density_weight = 0.12854295;
  double prefix_weight = 0.03140519;
  double neighborhood_weight = 0.35271970;
  double late_weight = 0.05727449;
  double critical_weight = 0.06596191;
  unsigned budget = 17;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
