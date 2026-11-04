// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57181796;
  double density_weight = 0.03042069;
  double prefix_weight = 0.36426712;
  double neighborhood_weight = 0.28754126;
  double late_weight = 0.04390888;
  double critical_weight = 0.30137294;
  unsigned budget = 30;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
