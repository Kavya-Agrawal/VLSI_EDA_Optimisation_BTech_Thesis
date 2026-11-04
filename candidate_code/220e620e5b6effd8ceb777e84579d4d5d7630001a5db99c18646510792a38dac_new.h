// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54486927;
  double density_weight = 0.50997405;
  double prefix_weight = 0.10470140;
  double neighborhood_weight = 0.22516670;
  double late_weight = 0.15909703;
  double critical_weight = 0.30339851;
  unsigned budget = 19;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
