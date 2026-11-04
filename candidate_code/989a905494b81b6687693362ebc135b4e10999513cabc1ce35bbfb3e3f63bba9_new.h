// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.37176597;
  double density_weight = 0.24125365;
  double prefix_weight = 0.49297810;
  double neighborhood_weight = 0.07939381;
  double late_weight = 0.03346192;
  double critical_weight = 0.22764113;
  unsigned budget = 40;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
