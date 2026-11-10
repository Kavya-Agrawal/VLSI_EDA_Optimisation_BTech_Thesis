// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23137336;
  double density_weight = 0.36778128;
  double prefix_weight = 0.06994248;
  double neighborhood_weight = 0.26710093;
  double late_weight = 0.15106918;
  double critical_weight = 0.36665161;
  unsigned budget = 28;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
