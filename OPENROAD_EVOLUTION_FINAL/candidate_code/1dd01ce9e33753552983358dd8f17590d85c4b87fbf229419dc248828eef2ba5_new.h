// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03983757;
  double density_weight = 0.56795150;
  double prefix_weight = 0.35291113;
  double neighborhood_weight = 0.35514695;
  double late_weight = 0.20092834;
  double critical_weight = 0.25228112;
  unsigned budget = 15;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
