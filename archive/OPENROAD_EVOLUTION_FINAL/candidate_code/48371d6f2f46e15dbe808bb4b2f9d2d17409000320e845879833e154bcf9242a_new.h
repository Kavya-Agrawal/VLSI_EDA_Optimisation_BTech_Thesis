// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12536966;
  double density_weight = 0.42319329;
  double prefix_weight = 0.30563922;
  double neighborhood_weight = 0.28368702;
  double late_weight = 0.00551527;
  double critical_weight = 0.23581554;
  unsigned budget = 27;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
