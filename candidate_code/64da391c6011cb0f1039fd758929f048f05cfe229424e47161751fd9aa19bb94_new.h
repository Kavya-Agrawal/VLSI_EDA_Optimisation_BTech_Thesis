// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65812399;
  double density_weight = 0.28242135;
  double prefix_weight = 0.02602981;
  double neighborhood_weight = 0.03268749;
  double late_weight = 0.29445115;
  double critical_weight = 0.06800781;
  unsigned budget = 27;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
