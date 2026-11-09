// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90512913;
  double density_weight = 0.34748075;
  double prefix_weight = 0.45790791;
  double neighborhood_weight = 0.26280812;
  double late_weight = 0.02815785;
  double critical_weight = 0.49636864;
  unsigned budget = 21;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
