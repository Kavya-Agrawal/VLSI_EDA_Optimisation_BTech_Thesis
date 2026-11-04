// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.83750786;
  double density_weight = 0.16901348;
  double prefix_weight = 0.23377535;
  double neighborhood_weight = 0.06681702;
  double late_weight = 0.28394704;
  double critical_weight = 0.26864003;
  unsigned budget = 12;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
