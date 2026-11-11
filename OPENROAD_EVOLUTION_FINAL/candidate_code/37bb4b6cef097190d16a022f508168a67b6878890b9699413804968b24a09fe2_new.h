// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.40179792;
  double density_weight = 0.09253827;
  double prefix_weight = 0.46181521;
  double neighborhood_weight = 0.37924060;
  double late_weight = 0.00307659;
  double critical_weight = 0.25103497;
  unsigned budget = 35;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
