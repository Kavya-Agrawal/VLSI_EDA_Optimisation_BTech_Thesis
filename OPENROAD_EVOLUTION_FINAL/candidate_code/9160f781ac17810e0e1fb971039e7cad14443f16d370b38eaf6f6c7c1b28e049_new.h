// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85776717;
  double density_weight = 0.34605942;
  double prefix_weight = 0.12445759;
  double neighborhood_weight = 0.13867241;
  double late_weight = 0.04621915;
  double critical_weight = 0.10442292;
  unsigned budget = 11;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
