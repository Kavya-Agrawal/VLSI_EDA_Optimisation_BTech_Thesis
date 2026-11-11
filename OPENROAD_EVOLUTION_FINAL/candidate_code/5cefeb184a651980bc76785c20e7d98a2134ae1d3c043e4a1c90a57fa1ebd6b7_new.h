// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71466956;
  double density_weight = 0.23775291;
  double prefix_weight = 0.38807837;
  double neighborhood_weight = 0.28099793;
  double late_weight = 0.15586851;
  double critical_weight = 0.39948991;
  unsigned budget = 35;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
