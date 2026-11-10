// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24808959;
  double density_weight = 0.35112967;
  double prefix_weight = 0.38732968;
  double neighborhood_weight = 0.39734932;
  double late_weight = 0.29062820;
  double critical_weight = 0.31940763;
  unsigned budget = 15;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
