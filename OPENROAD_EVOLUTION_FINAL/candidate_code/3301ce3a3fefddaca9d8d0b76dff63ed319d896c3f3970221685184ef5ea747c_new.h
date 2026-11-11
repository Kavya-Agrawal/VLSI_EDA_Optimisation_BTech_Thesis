// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41758432;
  double density_weight = 0.31498893;
  double prefix_weight = 0.34119197;
  double neighborhood_weight = 0.31257581;
  double late_weight = 0.24448537;
  double critical_weight = 0.01287096;
  unsigned budget = 22;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
