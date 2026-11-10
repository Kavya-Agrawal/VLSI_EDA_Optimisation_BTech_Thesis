// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73431138;
  double density_weight = 0.15272570;
  double prefix_weight = 0.18000500;
  double neighborhood_weight = 0.18163143;
  double late_weight = 0.14859520;
  double critical_weight = 0.23180559;
  unsigned budget = 38;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
