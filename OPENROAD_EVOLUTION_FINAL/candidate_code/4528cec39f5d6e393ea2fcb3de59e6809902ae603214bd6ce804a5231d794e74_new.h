// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72171643;
  double density_weight = 0.24508746;
  double prefix_weight = 0.43891308;
  double neighborhood_weight = 0.26157245;
  double late_weight = 0.19621606;
  double critical_weight = 0.34249029;
  unsigned budget = 17;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
