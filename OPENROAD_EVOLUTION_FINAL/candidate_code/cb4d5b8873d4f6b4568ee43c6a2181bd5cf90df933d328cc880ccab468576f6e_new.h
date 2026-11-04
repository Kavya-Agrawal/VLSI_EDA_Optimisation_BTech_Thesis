// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78203498;
  double density_weight = 0.35313600;
  double prefix_weight = 0.00079972;
  double neighborhood_weight = 0.14198347;
  double late_weight = 0.19310283;
  double critical_weight = 0.37937930;
  unsigned budget = 21;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
