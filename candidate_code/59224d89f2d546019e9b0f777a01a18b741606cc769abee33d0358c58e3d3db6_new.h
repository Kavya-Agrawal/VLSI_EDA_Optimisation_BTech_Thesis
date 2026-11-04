// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73762590;
  double density_weight = 0.18266383;
  double prefix_weight = 0.02771863;
  double neighborhood_weight = 0.14462302;
  double late_weight = 0.20554769;
  double critical_weight = 0.24324682;
  unsigned budget = 11;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
