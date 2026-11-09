// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62054562;
  double density_weight = 0.06402186;
  double prefix_weight = 0.15407290;
  double neighborhood_weight = 0.32613425;
  double late_weight = 0.10105199;
  double critical_weight = 0.21322942;
  unsigned budget = 14;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
