// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.58961576;
  double density_weight = 0.57221307;
  double prefix_weight = 0.24407228;
  double neighborhood_weight = 0.13334375;
  double late_weight = 0.22413494;
  double critical_weight = 0.40229111;
  unsigned budget = 31;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
