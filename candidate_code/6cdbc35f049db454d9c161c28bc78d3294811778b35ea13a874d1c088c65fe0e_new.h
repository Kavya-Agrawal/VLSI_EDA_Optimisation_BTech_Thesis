// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.72513244;
  double density_weight = 0.14482836;
  double prefix_weight = 0.00499886;
  double neighborhood_weight = 0.17549636;
  double late_weight = 0.18093427;
  double critical_weight = 0.22769158;
  unsigned budget = 22;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
