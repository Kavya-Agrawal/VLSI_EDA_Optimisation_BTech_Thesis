// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.89348298;
  double density_weight = 0.42273084;
  double prefix_weight = 0.21160818;
  double neighborhood_weight = 0.38801352;
  double late_weight = 0.16380568;
  double critical_weight = 0.20743649;
  unsigned budget = 38;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
