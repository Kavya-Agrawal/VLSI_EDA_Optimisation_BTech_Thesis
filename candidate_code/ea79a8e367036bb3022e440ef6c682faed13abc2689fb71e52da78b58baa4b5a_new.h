// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61286922;
  double density_weight = 0.34277027;
  double prefix_weight = 0.38015701;
  double neighborhood_weight = 0.21440616;
  double late_weight = 0.08924732;
  double critical_weight = 0.28373818;
  unsigned budget = 37;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
