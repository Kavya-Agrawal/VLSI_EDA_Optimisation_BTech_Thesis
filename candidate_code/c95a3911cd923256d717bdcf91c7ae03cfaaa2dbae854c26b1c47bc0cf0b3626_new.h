// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89521982;
  double density_weight = 0.50796838;
  double prefix_weight = 0.11986587;
  double neighborhood_weight = 0.17942940;
  double late_weight = 0.28806549;
  double critical_weight = 0.29959505;
  unsigned budget = 25;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
