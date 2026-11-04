// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.95629809;
  double density_weight = 0.54083873;
  double prefix_weight = 0.01335724;
  double neighborhood_weight = 0.08356833;
  double late_weight = 0.03422581;
  double critical_weight = 0.29594325;
  unsigned budget = 34;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
