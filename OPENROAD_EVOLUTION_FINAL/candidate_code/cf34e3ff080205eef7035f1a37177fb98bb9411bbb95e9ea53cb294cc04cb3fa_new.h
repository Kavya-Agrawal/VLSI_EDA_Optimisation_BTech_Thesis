// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.26310149;
  double density_weight = 0.54116797;
  double prefix_weight = 0.28335204;
  double neighborhood_weight = 0.24170604;
  double late_weight = 0.10437563;
  double critical_weight = 0.16524898;
  unsigned budget = 22;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
