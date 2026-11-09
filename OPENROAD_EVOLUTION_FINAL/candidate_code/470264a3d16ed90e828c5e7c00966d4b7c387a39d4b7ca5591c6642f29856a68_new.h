// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52060777;
  double density_weight = 0.35642066;
  double prefix_weight = 0.04150408;
  double neighborhood_weight = 0.34991801;
  double late_weight = 0.29073212;
  double critical_weight = 0.00811677;
  unsigned budget = 40;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
