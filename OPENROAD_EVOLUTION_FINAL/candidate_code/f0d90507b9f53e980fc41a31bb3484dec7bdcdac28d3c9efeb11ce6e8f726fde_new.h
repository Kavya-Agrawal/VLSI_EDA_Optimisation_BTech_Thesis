// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51809929;
  double density_weight = 0.07016514;
  double prefix_weight = 0.28221737;
  double neighborhood_weight = 0.38870095;
  double late_weight = 0.26473233;
  double critical_weight = 0.45627254;
  unsigned budget = 14;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
