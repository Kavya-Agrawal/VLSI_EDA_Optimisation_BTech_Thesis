// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60265271;
  double density_weight = 0.54275929;
  double prefix_weight = 0.04426619;
  double neighborhood_weight = 0.24156166;
  double late_weight = 0.26674434;
  double critical_weight = 0.36764668;
  unsigned budget = 31;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
