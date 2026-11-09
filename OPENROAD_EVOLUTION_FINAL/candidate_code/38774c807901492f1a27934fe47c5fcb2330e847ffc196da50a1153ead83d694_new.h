// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25019201;
  double density_weight = 0.52880058;
  double prefix_weight = 0.01323923;
  double neighborhood_weight = 0.37518831;
  double late_weight = 0.26191934;
  double critical_weight = 0.31974869;
  unsigned budget = 35;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
