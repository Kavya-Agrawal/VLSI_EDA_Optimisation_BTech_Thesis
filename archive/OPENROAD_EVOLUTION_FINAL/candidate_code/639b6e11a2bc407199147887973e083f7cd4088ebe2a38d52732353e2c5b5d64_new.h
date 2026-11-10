// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15328228;
  double density_weight = 0.52640859;
  double prefix_weight = 0.45954098;
  double neighborhood_weight = 0.10127605;
  double late_weight = 0.09476806;
  double critical_weight = 0.17035441;
  unsigned budget = 21;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
