// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10756683;
  double density_weight = 0.32832818;
  double prefix_weight = 0.25404119;
  double neighborhood_weight = 0.24569933;
  double late_weight = 0.22888973;
  double critical_weight = 0.06390308;
  unsigned budget = 30;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
