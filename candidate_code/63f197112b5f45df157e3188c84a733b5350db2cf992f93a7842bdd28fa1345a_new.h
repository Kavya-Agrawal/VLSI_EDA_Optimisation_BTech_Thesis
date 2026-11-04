// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54216980;
  double density_weight = 0.03489607;
  double prefix_weight = 0.25387010;
  double neighborhood_weight = 0.24380410;
  double late_weight = 0.03523912;
  double critical_weight = 0.42690169;
  unsigned budget = 38;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
