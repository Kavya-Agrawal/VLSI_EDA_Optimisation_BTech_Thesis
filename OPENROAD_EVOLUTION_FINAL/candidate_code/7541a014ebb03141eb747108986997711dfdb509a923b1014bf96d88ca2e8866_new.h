// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27719978;
  double density_weight = 0.42052165;
  double prefix_weight = 0.43642472;
  double neighborhood_weight = 0.16107855;
  double late_weight = 0.19177475;
  double critical_weight = 0.36665724;
  unsigned budget = 29;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
