// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58999507;
  double density_weight = 0.44579024;
  double prefix_weight = 0.26310566;
  double neighborhood_weight = 0.11723205;
  double late_weight = 0.06605477;
  double critical_weight = 0.33830522;
  unsigned budget = 21;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
