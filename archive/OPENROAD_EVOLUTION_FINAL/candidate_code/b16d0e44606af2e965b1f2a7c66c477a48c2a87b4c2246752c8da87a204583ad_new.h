// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80844288;
  double density_weight = 0.25615870;
  double prefix_weight = 0.31099693;
  double neighborhood_weight = 0.16242618;
  double late_weight = 0.06477321;
  double critical_weight = 0.23097848;
  unsigned budget = 30;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
