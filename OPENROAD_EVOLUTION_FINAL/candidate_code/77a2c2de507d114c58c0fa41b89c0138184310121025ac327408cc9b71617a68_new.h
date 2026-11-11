// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43938140;
  double density_weight = 0.13018039;
  double prefix_weight = 0.26222713;
  double neighborhood_weight = 0.38398763;
  double late_weight = 0.15851706;
  double critical_weight = 0.20720373;
  unsigned budget = 27;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
