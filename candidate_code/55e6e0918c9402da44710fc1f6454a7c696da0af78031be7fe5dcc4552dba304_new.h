// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24376869;
  double density_weight = 0.56668578;
  double prefix_weight = 0.30432977;
  double neighborhood_weight = 0.35917665;
  double late_weight = 0.20660272;
  double critical_weight = 0.42706491;
  unsigned budget = 33;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
