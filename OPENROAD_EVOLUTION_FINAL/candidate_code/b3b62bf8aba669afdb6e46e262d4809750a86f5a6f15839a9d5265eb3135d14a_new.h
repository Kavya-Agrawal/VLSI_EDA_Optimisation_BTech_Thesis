// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.81451024;
  double density_weight = 0.04096818;
  double prefix_weight = 0.07688592;
  double neighborhood_weight = 0.11216576;
  double late_weight = 0.10692342;
  double critical_weight = 0.18120075;
  unsigned budget = 6;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
