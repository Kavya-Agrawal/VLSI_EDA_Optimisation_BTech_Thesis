// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07649378;
  double density_weight = 0.59471907;
  double prefix_weight = 0.09461000;
  double neighborhood_weight = 0.26387299;
  double late_weight = 0.12160941;
  double critical_weight = 0.17049317;
  unsigned budget = 26;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
