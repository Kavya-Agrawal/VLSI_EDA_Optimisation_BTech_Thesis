// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44798884;
  double density_weight = 0.49957060;
  double prefix_weight = 0.02705159;
  double neighborhood_weight = 0.38391311;
  double late_weight = 0.20822521;
  double critical_weight = 0.07824840;
  unsigned budget = 26;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
