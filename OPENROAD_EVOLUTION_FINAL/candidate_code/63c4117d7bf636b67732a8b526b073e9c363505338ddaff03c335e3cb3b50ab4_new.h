// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.06088318;
  double density_weight = 0.55295669;
  double prefix_weight = 0.15289065;
  double neighborhood_weight = 0.15324513;
  double late_weight = 0.12976022;
  double critical_weight = 0.16228676;
  unsigned budget = 6;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
