// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76030612;
  double density_weight = 0.59416329;
  double prefix_weight = 0.33765163;
  double neighborhood_weight = 0.35632526;
  double late_weight = 0.25196138;
  double critical_weight = 0.28706875;
  unsigned budget = 27;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
