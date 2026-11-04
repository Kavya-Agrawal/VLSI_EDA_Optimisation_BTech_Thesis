// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65566889;
  double density_weight = 0.06497279;
  double prefix_weight = 0.22984177;
  double neighborhood_weight = 0.05251527;
  double late_weight = 0.17848227;
  double critical_weight = 0.38971083;
  unsigned budget = 23;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
