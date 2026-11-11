// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.53904352;
  double density_weight = 0.26188109;
  double prefix_weight = 0.36982668;
  double neighborhood_weight = 0.28927096;
  double late_weight = 0.25091287;
  double critical_weight = 0.14035930;
  unsigned budget = 17;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
