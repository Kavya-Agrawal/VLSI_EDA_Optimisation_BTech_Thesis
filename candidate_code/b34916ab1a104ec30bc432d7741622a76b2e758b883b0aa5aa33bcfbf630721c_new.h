// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70227929;
  double density_weight = 0.14316255;
  double prefix_weight = 0.16201034;
  double neighborhood_weight = 0.10928368;
  double late_weight = 0.11717599;
  double critical_weight = 0.35463816;
  unsigned budget = 22;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
