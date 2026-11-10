// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.91866181;
  double density_weight = 0.00746371;
  double prefix_weight = 0.24213528;
  double neighborhood_weight = 0.22287858;
  double late_weight = 0.04910831;
  double critical_weight = 0.26820379;
  unsigned budget = 7;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
