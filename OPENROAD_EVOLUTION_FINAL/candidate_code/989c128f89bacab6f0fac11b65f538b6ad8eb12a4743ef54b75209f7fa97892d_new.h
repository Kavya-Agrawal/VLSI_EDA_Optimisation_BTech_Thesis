// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57783408;
  double density_weight = 0.09940238;
  double prefix_weight = 0.24368875;
  double neighborhood_weight = 0.14126219;
  double late_weight = 0.13746382;
  double critical_weight = 0.42283338;
  unsigned budget = 31;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
