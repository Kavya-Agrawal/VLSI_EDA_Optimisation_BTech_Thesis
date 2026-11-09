// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.52707791;
  double density_weight = 0.06034554;
  double prefix_weight = 0.20865087;
  double neighborhood_weight = 0.35549235;
  double late_weight = 0.13508542;
  double critical_weight = 0.44322978;
  unsigned budget = 16;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
