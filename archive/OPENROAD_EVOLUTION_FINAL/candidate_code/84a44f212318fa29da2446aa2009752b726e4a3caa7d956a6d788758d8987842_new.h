// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82303699;
  double density_weight = 0.59454901;
  double prefix_weight = 0.29718955;
  double neighborhood_weight = 0.23050437;
  double late_weight = 0.26801785;
  double critical_weight = 0.08491653;
  unsigned budget = 33;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
