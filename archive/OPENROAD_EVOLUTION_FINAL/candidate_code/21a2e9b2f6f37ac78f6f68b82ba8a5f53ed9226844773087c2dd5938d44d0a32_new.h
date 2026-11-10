// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.11619981;
  double density_weight = 0.44134461;
  double prefix_weight = 0.18491907;
  double neighborhood_weight = 0.05304943;
  double late_weight = 0.25140613;
  double critical_weight = 0.30820871;
  unsigned budget = 13;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
