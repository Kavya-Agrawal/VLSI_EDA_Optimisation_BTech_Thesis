// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.96065029;
  double density_weight = 0.01378795;
  double prefix_weight = 0.49226090;
  double neighborhood_weight = 0.22245122;
  double late_weight = 0.21679223;
  double critical_weight = 0.31158600;
  unsigned budget = 10;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
