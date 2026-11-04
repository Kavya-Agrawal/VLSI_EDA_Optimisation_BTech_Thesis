// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.26869474;
  double density_weight = 0.41231415;
  double prefix_weight = 0.46641479;
  double neighborhood_weight = 0.13098738;
  double late_weight = 0.11091511;
  double critical_weight = 0.30868552;
  unsigned budget = 30;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
