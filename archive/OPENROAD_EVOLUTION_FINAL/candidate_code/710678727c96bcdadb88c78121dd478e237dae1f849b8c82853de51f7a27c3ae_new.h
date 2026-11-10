// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46471303;
  double density_weight = 0.20628413;
  double prefix_weight = 0.04847829;
  double neighborhood_weight = 0.15973403;
  double late_weight = 0.10928306;
  double critical_weight = 0.25710669;
  unsigned budget = 16;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
