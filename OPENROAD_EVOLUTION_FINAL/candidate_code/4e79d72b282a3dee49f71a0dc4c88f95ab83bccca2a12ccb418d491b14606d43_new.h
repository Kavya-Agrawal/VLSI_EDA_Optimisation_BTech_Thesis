// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58795627;
  double density_weight = 0.22594374;
  double prefix_weight = 0.07382616;
  double neighborhood_weight = 0.15717481;
  double late_weight = 0.23546986;
  double critical_weight = 0.17597633;
  unsigned budget = 20;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
