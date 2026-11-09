// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10410972;
  double density_weight = 0.12444018;
  double prefix_weight = 0.40446925;
  double neighborhood_weight = 0.07920850;
  double late_weight = 0.12434204;
  double critical_weight = 0.18193605;
  unsigned budget = 25;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
