// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.71355525;
  double density_weight = 0.20462238;
  double prefix_weight = 0.44962622;
  double neighborhood_weight = 0.17627065;
  double late_weight = 0.06980639;
  double critical_weight = 0.31948565;
  unsigned budget = 6;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
