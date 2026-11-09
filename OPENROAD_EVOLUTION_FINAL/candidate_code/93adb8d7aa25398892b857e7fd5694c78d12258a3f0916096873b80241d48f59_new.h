// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.26865671;
  double density_weight = 0.41853228;
  double prefix_weight = 0.34255921;
  double neighborhood_weight = 0.24075627;
  double late_weight = 0.15660143;
  double critical_weight = 0.34700558;
  unsigned budget = 22;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
