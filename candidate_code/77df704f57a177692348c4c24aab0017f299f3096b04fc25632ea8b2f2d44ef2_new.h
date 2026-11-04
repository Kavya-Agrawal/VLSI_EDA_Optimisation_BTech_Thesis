// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.75927345;
  double density_weight = 0.40160492;
  double prefix_weight = 0.17210115;
  double neighborhood_weight = 0.34262523;
  double late_weight = 0.00652540;
  double critical_weight = 0.26439822;
  unsigned budget = 38;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
