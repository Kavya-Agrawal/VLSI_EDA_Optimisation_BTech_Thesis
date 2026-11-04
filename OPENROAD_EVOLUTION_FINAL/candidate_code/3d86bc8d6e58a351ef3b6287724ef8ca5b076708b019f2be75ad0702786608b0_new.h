// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.33441505;
  double density_weight = 0.55454786;
  double prefix_weight = 0.45284221;
  double neighborhood_weight = 0.06181000;
  double late_weight = 0.05949681;
  double critical_weight = 0.09199339;
  unsigned budget = 11;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
