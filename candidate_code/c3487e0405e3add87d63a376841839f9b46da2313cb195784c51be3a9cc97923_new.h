// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.28091446;
  double density_weight = 0.48172397;
  double prefix_weight = 0.34731148;
  double neighborhood_weight = 0.10182640;
  double late_weight = 0.04775033;
  double critical_weight = 0.25167514;
  unsigned budget = 20;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
