// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97758964;
  double density_weight = 0.41951511;
  double prefix_weight = 0.22169764;
  double neighborhood_weight = 0.26074441;
  double late_weight = 0.05030113;
  double critical_weight = 0.04717840;
  unsigned budget = 37;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
