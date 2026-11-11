// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64399390;
  double density_weight = 0.01117028;
  double prefix_weight = 0.20006314;
  double neighborhood_weight = 0.08938265;
  double late_weight = 0.23585653;
  double critical_weight = 0.11750936;
  unsigned budget = 26;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
