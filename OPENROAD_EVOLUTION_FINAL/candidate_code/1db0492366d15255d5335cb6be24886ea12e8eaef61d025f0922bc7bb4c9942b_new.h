// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62268107;
  double density_weight = 0.02999498;
  double prefix_weight = 0.25675394;
  double neighborhood_weight = 0.11301771;
  double late_weight = 0.16901654;
  double critical_weight = 0.18298741;
  unsigned budget = 21;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
