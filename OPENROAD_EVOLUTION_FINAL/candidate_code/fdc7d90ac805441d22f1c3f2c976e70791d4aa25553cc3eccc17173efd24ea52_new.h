// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.87325153;
  double density_weight = 0.56076233;
  double prefix_weight = 0.10384444;
  double neighborhood_weight = 0.27868086;
  double late_weight = 0.00128532;
  double critical_weight = 0.42180885;
  unsigned budget = 28;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
