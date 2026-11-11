// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86507520;
  double density_weight = 0.22313327;
  double prefix_weight = 0.22380260;
  double neighborhood_weight = 0.19197137;
  double late_weight = 0.13777087;
  double critical_weight = 0.20208368;
  unsigned budget = 32;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
