// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01175122;
  double density_weight = 0.38305255;
  double prefix_weight = 0.23725500;
  double neighborhood_weight = 0.23950798;
  double late_weight = 0.08092495;
  double critical_weight = 0.14054212;
  unsigned budget = 33;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
