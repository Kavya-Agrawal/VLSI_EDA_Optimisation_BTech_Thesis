// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99440365;
  double density_weight = 0.04030060;
  double prefix_weight = 0.34948685;
  double neighborhood_weight = 0.28564218;
  double late_weight = 0.13894082;
  double critical_weight = 0.26257923;
  unsigned budget = 27;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
