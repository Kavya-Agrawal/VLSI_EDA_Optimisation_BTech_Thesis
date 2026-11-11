// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51991328;
  double density_weight = 0.42461281;
  double prefix_weight = 0.39654995;
  double neighborhood_weight = 0.38511532;
  double late_weight = 0.00505708;
  double critical_weight = 0.38798173;
  unsigned budget = 34;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
