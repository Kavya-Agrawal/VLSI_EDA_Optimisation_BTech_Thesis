// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41682444;
  double density_weight = 0.34757463;
  double prefix_weight = 0.35969733;
  double neighborhood_weight = 0.37378817;
  double late_weight = 0.01816766;
  double critical_weight = 0.18598013;
  unsigned budget = 18;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
