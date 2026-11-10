// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.77838218;
  double density_weight = 0.49609108;
  double prefix_weight = 0.32689513;
  double neighborhood_weight = 0.16844066;
  double late_weight = 0.25680087;
  double critical_weight = 0.11277490;
  unsigned budget = 11;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
