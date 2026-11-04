// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84017437;
  double density_weight = 0.56042025;
  double prefix_weight = 0.02159432;
  double neighborhood_weight = 0.12012716;
  double late_weight = 0.04774087;
  double critical_weight = 0.35514599;
  unsigned budget = 32;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
