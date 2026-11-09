// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.93324817;
  double density_weight = 0.56631215;
  double prefix_weight = 0.42184673;
  double neighborhood_weight = 0.32247359;
  double late_weight = 0.22354904;
  double critical_weight = 0.22850726;
  unsigned budget = 13;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
