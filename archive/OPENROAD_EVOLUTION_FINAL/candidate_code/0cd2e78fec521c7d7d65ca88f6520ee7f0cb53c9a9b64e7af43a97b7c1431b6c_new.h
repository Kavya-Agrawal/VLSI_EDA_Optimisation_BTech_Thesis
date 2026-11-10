// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.81532396;
  double density_weight = 0.12467445;
  double prefix_weight = 0.41498646;
  double neighborhood_weight = 0.08316594;
  double late_weight = 0.18001075;
  double critical_weight = 0.17848583;
  unsigned budget = 5;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
