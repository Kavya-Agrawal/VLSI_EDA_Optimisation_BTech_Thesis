// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.36876753;
  double density_weight = 0.52415707;
  double prefix_weight = 0.32294464;
  double neighborhood_weight = 0.25829862;
  double late_weight = 0.00513647;
  double critical_weight = 0.09939844;
  unsigned budget = 9;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
