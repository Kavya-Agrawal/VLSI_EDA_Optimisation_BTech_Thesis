// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45147112;
  double density_weight = 0.45242145;
  double prefix_weight = 0.30534749;
  double neighborhood_weight = 0.16034240;
  double late_weight = 0.19546539;
  double critical_weight = 0.24575035;
  unsigned budget = 40;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
