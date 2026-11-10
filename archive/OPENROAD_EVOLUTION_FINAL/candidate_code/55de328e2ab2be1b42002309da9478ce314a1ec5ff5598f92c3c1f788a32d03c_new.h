// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04662155;
  double density_weight = 0.45539324;
  double prefix_weight = 0.16925564;
  double neighborhood_weight = 0.07594364;
  double late_weight = 0.13361335;
  double critical_weight = 0.35011884;
  unsigned budget = 16;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
