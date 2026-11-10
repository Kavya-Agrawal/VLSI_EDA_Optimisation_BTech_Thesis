// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.11507821;
  double density_weight = 0.42577945;
  double prefix_weight = 0.40450537;
  double neighborhood_weight = 0.15980223;
  double late_weight = 0.13536982;
  double critical_weight = 0.14231963;
  unsigned budget = 25;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
