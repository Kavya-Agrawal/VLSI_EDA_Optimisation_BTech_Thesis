// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86643618;
  double density_weight = 0.48229166;
  double prefix_weight = 0.21134812;
  double neighborhood_weight = 0.38196656;
  double late_weight = 0.29192638;
  double critical_weight = 0.02050891;
  unsigned budget = 17;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
