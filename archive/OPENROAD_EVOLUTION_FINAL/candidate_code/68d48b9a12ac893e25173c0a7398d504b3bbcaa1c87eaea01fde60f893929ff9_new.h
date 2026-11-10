// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65309828;
  double density_weight = 0.40640873;
  double prefix_weight = 0.28783246;
  double neighborhood_weight = 0.16148304;
  double late_weight = 0.03598728;
  double critical_weight = 0.07384421;
  unsigned budget = 39;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
