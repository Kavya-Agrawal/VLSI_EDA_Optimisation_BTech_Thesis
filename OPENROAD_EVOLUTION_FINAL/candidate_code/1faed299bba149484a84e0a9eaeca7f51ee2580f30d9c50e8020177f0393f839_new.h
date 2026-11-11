// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97794997;
  double density_weight = 0.45651376;
  double prefix_weight = 0.01930425;
  double neighborhood_weight = 0.02942450;
  double late_weight = 0.27193871;
  double critical_weight = 0.40299248;
  unsigned budget = 7;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
