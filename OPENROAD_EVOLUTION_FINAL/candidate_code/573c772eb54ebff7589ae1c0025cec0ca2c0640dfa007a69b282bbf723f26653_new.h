// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74952078;
  double density_weight = 0.10145682;
  double prefix_weight = 0.22301779;
  double neighborhood_weight = 0.33048663;
  double late_weight = 0.11851790;
  double critical_weight = 0.14047613;
  unsigned budget = 12;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
