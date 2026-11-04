// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17277225;
  double density_weight = 0.54820830;
  double prefix_weight = 0.46760042;
  double neighborhood_weight = 0.15471671;
  double late_weight = 0.27887819;
  double critical_weight = 0.04262921;
  unsigned budget = 18;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
