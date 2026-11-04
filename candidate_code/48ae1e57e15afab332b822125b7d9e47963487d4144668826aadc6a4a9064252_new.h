// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56179760;
  double density_weight = 0.11404068;
  double prefix_weight = 0.15870276;
  double neighborhood_weight = 0.28879319;
  double late_weight = 0.05234061;
  double critical_weight = 0.17857549;
  unsigned budget = 32;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
