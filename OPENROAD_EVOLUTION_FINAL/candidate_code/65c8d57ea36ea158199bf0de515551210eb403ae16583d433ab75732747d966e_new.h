// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09384170;
  double density_weight = 0.47290949;
  double prefix_weight = 0.01637778;
  double neighborhood_weight = 0.32977223;
  double late_weight = 0.17246371;
  double critical_weight = 0.25918850;
  unsigned budget = 34;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
