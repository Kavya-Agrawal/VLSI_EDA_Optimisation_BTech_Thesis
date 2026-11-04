// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.32585704;
  double density_weight = 0.12977989;
  double prefix_weight = 0.49822117;
  double neighborhood_weight = 0.06008310;
  double late_weight = 0.16840265;
  double critical_weight = 0.16283079;
  unsigned budget = 17;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
