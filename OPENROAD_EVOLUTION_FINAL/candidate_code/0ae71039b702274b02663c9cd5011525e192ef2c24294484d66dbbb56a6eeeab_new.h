// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.50286282;
  double density_weight = 0.47224242;
  double prefix_weight = 0.12970261;
  double neighborhood_weight = 0.19685634;
  double late_weight = 0.25786415;
  double critical_weight = 0.40060970;
  unsigned budget = 16;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
