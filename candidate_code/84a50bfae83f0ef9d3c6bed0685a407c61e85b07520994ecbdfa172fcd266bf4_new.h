// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65220284;
  double density_weight = 0.31036922;
  double prefix_weight = 0.11177741;
  double neighborhood_weight = 0.39965502;
  double late_weight = 0.02973562;
  double critical_weight = 0.02447592;
  unsigned budget = 19;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
