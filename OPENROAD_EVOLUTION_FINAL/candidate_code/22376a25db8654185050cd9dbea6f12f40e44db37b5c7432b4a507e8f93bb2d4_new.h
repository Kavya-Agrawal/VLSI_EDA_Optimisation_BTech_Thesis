// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.10276741;
  double density_weight = 0.09884024;
  double prefix_weight = 0.19170297;
  double neighborhood_weight = 0.38762587;
  double late_weight = 0.17243213;
  double critical_weight = 0.26129308;
  unsigned budget = 5;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
