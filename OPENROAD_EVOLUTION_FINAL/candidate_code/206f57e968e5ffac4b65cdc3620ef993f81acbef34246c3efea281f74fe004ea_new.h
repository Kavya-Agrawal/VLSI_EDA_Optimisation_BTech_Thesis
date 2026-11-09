// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56094651;
  double density_weight = 0.14061209;
  double prefix_weight = 0.12894774;
  double neighborhood_weight = 0.01721924;
  double late_weight = 0.09667058;
  double critical_weight = 0.48666458;
  unsigned budget = 25;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
