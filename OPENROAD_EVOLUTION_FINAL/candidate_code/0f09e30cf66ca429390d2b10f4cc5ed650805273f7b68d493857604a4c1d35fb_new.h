// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84490628;
  double density_weight = 0.19948418;
  double prefix_weight = 0.42872148;
  double neighborhood_weight = 0.26232116;
  double late_weight = 0.20142891;
  double critical_weight = 0.44224296;
  unsigned budget = 38;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
