// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41031766;
  double density_weight = 0.41859671;
  double prefix_weight = 0.42674828;
  double neighborhood_weight = 0.10453085;
  double late_weight = 0.04040274;
  double critical_weight = 0.09502925;
  unsigned budget = 6;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
