// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.13557470;
  double density_weight = 0.20765860;
  double prefix_weight = 0.29089935;
  double neighborhood_weight = 0.19193629;
  double late_weight = 0.25617524;
  double critical_weight = 0.43558578;
  unsigned budget = 5;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
