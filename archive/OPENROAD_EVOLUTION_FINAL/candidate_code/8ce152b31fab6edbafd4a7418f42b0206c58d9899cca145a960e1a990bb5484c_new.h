// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15586482;
  double density_weight = 0.12360405;
  double prefix_weight = 0.35580854;
  double neighborhood_weight = 0.21663011;
  double late_weight = 0.02007955;
  double critical_weight = 0.20396332;
  unsigned budget = 19;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
