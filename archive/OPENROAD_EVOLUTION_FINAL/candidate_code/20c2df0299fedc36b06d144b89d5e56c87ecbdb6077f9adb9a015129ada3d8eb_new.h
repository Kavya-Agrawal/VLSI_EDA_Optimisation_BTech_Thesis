// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23080522;
  double density_weight = 0.24186743;
  double prefix_weight = 0.03121596;
  double neighborhood_weight = 0.37815391;
  double late_weight = 0.14239170;
  double critical_weight = 0.28085268;
  unsigned budget = 32;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
