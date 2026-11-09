// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.77494249;
  double density_weight = 0.35168677;
  double prefix_weight = 0.07174201;
  double neighborhood_weight = 0.35505580;
  double late_weight = 0.01137609;
  double critical_weight = 0.44270716;
  unsigned budget = 17;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
