// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.68940812;
  double density_weight = 0.13714752;
  double prefix_weight = 0.23251386;
  double neighborhood_weight = 0.03762881;
  double late_weight = 0.12052422;
  double critical_weight = 0.30668621;
  unsigned budget = 20;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
