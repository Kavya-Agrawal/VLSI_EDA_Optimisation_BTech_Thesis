// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71434267;
  double density_weight = 0.30530873;
  double prefix_weight = 0.16346344;
  double neighborhood_weight = 0.13902617;
  double late_weight = 0.10452870;
  double critical_weight = 0.27792524;
  unsigned budget = 29;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
