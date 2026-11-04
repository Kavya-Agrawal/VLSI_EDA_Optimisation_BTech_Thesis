// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21310275;
  double density_weight = 0.37478590;
  double prefix_weight = 0.26580109;
  double neighborhood_weight = 0.06129103;
  double late_weight = 0.28383704;
  double critical_weight = 0.34524993;
  unsigned budget = 40;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
