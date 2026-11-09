// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02610566;
  double density_weight = 0.11492001;
  double prefix_weight = 0.47458592;
  double neighborhood_weight = 0.19539490;
  double late_weight = 0.15023633;
  double critical_weight = 0.22162648;
  unsigned budget = 13;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
