// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44501372;
  double density_weight = 0.22663508;
  double prefix_weight = 0.33543099;
  double neighborhood_weight = 0.17751790;
  double late_weight = 0.11266733;
  double critical_weight = 0.11707116;
  unsigned budget = 22;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
