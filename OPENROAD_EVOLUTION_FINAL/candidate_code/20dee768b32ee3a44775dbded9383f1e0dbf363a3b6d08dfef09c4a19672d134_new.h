// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57222696;
  double density_weight = 0.39299335;
  double prefix_weight = 0.42023736;
  double neighborhood_weight = 0.12178970;
  double late_weight = 0.13136658;
  double critical_weight = 0.30440709;
  unsigned budget = 29;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
