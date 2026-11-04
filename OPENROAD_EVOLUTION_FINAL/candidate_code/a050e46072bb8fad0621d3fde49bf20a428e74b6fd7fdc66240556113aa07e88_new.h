// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.60303906;
  double density_weight = 0.10134763;
  double prefix_weight = 0.30861108;
  double neighborhood_weight = 0.05439323;
  double late_weight = 0.28297270;
  double critical_weight = 0.43974796;
  unsigned budget = 7;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
