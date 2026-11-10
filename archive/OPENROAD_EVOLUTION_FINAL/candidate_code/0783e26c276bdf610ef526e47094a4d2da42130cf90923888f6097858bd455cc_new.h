// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38330465;
  double density_weight = 0.25636841;
  double prefix_weight = 0.48117516;
  double neighborhood_weight = 0.13718974;
  double late_weight = 0.03331090;
  double critical_weight = 0.17860907;
  unsigned budget = 16;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
