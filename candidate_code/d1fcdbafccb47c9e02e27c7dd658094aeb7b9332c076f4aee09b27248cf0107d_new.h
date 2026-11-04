// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.61883230;
  double density_weight = 0.18789382;
  double prefix_weight = 0.30265299;
  double neighborhood_weight = 0.39641712;
  double late_weight = 0.18214480;
  double critical_weight = 0.00167537;
  unsigned budget = 28;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
