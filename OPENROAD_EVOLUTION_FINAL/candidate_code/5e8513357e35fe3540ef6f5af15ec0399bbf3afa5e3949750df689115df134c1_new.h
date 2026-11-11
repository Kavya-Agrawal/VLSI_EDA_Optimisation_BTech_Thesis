// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60879661;
  double density_weight = 0.15706678;
  double prefix_weight = 0.44654320;
  double neighborhood_weight = 0.20536732;
  double late_weight = 0.29088627;
  double critical_weight = 0.24867004;
  unsigned budget = 13;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
