// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34129841;
  double density_weight = 0.15194907;
  double prefix_weight = 0.30988760;
  double neighborhood_weight = 0.32978269;
  double late_weight = 0.13026972;
  double critical_weight = 0.32300588;
  unsigned budget = 40;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
