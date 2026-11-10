// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20626652;
  double density_weight = 0.11507604;
  double prefix_weight = 0.33802823;
  double neighborhood_weight = 0.31665242;
  double late_weight = 0.15896416;
  double critical_weight = 0.13205977;
  unsigned budget = 27;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
