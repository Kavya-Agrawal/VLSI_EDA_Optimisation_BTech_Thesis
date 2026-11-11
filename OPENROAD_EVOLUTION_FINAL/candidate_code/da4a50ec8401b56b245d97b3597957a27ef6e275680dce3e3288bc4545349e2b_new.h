// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.91173099;
  double density_weight = 0.41261387;
  double prefix_weight = 0.37885934;
  double neighborhood_weight = 0.39373570;
  double late_weight = 0.08243618;
  double critical_weight = 0.26672005;
  unsigned budget = 35;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
