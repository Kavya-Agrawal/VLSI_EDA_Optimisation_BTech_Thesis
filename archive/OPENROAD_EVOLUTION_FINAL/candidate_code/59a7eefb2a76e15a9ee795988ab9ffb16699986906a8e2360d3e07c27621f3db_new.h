// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.74923995;
  double density_weight = 0.06248316;
  double prefix_weight = 0.05632196;
  double neighborhood_weight = 0.26441324;
  double late_weight = 0.29766244;
  double critical_weight = 0.25154428;
  unsigned budget = 11;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
