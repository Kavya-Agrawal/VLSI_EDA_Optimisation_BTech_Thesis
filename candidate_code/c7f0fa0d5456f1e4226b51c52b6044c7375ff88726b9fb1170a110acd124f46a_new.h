// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.75847791;
  double density_weight = 0.22893061;
  double prefix_weight = 0.09147147;
  double neighborhood_weight = 0.31461682;
  double late_weight = 0.04194778;
  double critical_weight = 0.20268325;
  unsigned budget = 10;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
