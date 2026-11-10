// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.16986760;
  double density_weight = 0.20456494;
  double prefix_weight = 0.22983690;
  double neighborhood_weight = 0.11071157;
  double late_weight = 0.05590244;
  double critical_weight = 0.01334200;
  unsigned budget = 36;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
