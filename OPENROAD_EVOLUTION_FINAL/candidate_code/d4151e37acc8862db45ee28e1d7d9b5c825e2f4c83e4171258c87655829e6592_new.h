// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25378515;
  double density_weight = 0.18733996;
  double prefix_weight = 0.42849963;
  double neighborhood_weight = 0.31326342;
  double late_weight = 0.15384352;
  double critical_weight = 0.02181819;
  unsigned budget = 25;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
