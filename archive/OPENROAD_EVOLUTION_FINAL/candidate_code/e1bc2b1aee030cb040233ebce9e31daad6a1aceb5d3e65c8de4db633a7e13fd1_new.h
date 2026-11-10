// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.42902121;
  double density_weight = 0.33207937;
  double prefix_weight = 0.46497255;
  double neighborhood_weight = 0.29140516;
  double late_weight = 0.08206929;
  double critical_weight = 0.14797997;
  unsigned budget = 7;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
