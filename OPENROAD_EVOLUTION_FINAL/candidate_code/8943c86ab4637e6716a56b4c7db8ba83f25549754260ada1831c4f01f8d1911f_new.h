// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04197225;
  double density_weight = 0.05751942;
  double prefix_weight = 0.48988274;
  double neighborhood_weight = 0.10131905;
  double late_weight = 0.03541380;
  double critical_weight = 0.40939962;
  unsigned budget = 23;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
