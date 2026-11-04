// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.91249871;
  double density_weight = 0.12240995;
  double prefix_weight = 0.39534747;
  double neighborhood_weight = 0.16897293;
  double late_weight = 0.12855767;
  double critical_weight = 0.04863063;
  unsigned budget = 5;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
