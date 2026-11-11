// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85721472;
  double density_weight = 0.34773295;
  double prefix_weight = 0.22763006;
  double neighborhood_weight = 0.28047730;
  double late_weight = 0.04441536;
  double critical_weight = 0.40316724;
  unsigned budget = 32;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
