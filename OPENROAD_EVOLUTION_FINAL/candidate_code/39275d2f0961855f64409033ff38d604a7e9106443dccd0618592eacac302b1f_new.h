// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93379253;
  double density_weight = 0.15232342;
  double prefix_weight = 0.35642365;
  double neighborhood_weight = 0.15022378;
  double late_weight = 0.07474158;
  double critical_weight = 0.19376613;
  unsigned budget = 31;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
