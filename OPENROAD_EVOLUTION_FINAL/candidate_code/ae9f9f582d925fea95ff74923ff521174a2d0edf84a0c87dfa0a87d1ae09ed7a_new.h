// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07071420;
  double density_weight = 0.43374105;
  double prefix_weight = 0.33782581;
  double neighborhood_weight = 0.39462181;
  double late_weight = 0.19860135;
  double critical_weight = 0.03162747;
  unsigned budget = 22;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
