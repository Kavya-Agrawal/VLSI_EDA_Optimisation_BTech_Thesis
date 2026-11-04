// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94984850;
  double density_weight = 0.40150436;
  double prefix_weight = 0.36023897;
  double neighborhood_weight = 0.23539524;
  double late_weight = 0.10870619;
  double critical_weight = 0.16154557;
  unsigned budget = 31;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
