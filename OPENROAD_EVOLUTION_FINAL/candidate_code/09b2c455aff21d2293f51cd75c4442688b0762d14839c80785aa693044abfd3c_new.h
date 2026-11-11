// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93965499;
  double density_weight = 0.03858517;
  double prefix_weight = 0.30712320;
  double neighborhood_weight = 0.23493484;
  double late_weight = 0.07856874;
  double critical_weight = 0.01015052;
  unsigned budget = 32;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
