// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74352333;
  double density_weight = 0.52241344;
  double prefix_weight = 0.11057256;
  double neighborhood_weight = 0.32063158;
  double late_weight = 0.09229716;
  double critical_weight = 0.19982745;
  unsigned budget = 16;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
