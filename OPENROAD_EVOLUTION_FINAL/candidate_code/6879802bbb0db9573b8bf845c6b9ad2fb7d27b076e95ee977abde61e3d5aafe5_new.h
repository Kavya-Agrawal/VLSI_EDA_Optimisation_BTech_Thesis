// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97569435;
  double density_weight = 0.52499248;
  double prefix_weight = 0.06360549;
  double neighborhood_weight = 0.35004868;
  double late_weight = 0.08692766;
  double critical_weight = 0.25594838;
  unsigned budget = 17;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
