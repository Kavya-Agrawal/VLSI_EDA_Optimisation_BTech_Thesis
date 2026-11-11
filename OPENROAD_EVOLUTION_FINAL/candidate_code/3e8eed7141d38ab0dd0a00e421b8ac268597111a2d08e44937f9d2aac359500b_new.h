// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47851292;
  double density_weight = 0.29952502;
  double prefix_weight = 0.35686386;
  double neighborhood_weight = 0.37683552;
  double late_weight = 0.14786104;
  double critical_weight = 0.28296697;
  unsigned budget = 11;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
