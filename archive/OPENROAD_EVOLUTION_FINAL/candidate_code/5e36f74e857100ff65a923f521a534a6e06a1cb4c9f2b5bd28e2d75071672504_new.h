// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76090554;
  double density_weight = 0.41477921;
  double prefix_weight = 0.06347739;
  double neighborhood_weight = 0.29039203;
  double late_weight = 0.26911507;
  double critical_weight = 0.30313343;
  unsigned budget = 19;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
