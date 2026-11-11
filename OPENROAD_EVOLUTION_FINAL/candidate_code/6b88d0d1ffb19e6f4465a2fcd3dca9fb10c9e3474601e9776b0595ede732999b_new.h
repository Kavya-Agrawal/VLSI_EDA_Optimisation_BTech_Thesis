// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14300074;
  double density_weight = 0.32284420;
  double prefix_weight = 0.14079155;
  double neighborhood_weight = 0.14705264;
  double late_weight = 0.26292871;
  double critical_weight = 0.21705769;
  unsigned budget = 28;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
