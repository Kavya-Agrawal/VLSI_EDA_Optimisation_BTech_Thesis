// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.70034106;
  double density_weight = 0.17899347;
  double prefix_weight = 0.08001037;
  double neighborhood_weight = 0.18612710;
  double late_weight = 0.09836841;
  double critical_weight = 0.29522294;
  unsigned budget = 12;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
