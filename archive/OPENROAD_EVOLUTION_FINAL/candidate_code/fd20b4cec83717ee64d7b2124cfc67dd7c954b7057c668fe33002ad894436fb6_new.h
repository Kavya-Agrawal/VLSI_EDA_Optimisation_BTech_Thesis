// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.05766678;
  double density_weight = 0.27328976;
  double prefix_weight = 0.24218967;
  double neighborhood_weight = 0.14676190;
  double late_weight = 0.25001601;
  double critical_weight = 0.21966421;
  unsigned budget = 28;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
