// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.94549543;
  double density_weight = 0.35759979;
  double prefix_weight = 0.24402964;
  double neighborhood_weight = 0.31440341;
  double late_weight = 0.26061878;
  double critical_weight = 0.13912622;
  unsigned budget = 31;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
