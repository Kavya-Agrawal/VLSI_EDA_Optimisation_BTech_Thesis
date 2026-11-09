// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09966945;
  double density_weight = 0.11849289;
  double prefix_weight = 0.18185521;
  double neighborhood_weight = 0.10030611;
  double late_weight = 0.19361438;
  double critical_weight = 0.29607415;
  unsigned budget = 20;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
