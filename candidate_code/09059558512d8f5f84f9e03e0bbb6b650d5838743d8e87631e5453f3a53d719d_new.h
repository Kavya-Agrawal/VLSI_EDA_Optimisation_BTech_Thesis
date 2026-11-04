// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97307348;
  double density_weight = 0.39298401;
  double prefix_weight = 0.39735724;
  double neighborhood_weight = 0.23237764;
  double late_weight = 0.13102105;
  double critical_weight = 0.04039109;
  unsigned budget = 39;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
