// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04568301;
  double density_weight = 0.43120990;
  double prefix_weight = 0.41739487;
  double neighborhood_weight = 0.09421962;
  double late_weight = 0.10240886;
  double critical_weight = 0.00542367;
  unsigned budget = 27;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
