// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20631285;
  double density_weight = 0.26800896;
  double prefix_weight = 0.01151560;
  double neighborhood_weight = 0.10065312;
  double late_weight = 0.08119301;
  double critical_weight = 0.39690524;
  unsigned budget = 33;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
