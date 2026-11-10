// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38398024;
  double density_weight = 0.53297141;
  double prefix_weight = 0.46485305;
  double neighborhood_weight = 0.16852569;
  double late_weight = 0.09073416;
  double critical_weight = 0.00828979;
  unsigned budget = 6;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
