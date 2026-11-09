// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76318186;
  double density_weight = 0.54914583;
  double prefix_weight = 0.18376942;
  double neighborhood_weight = 0.13635726;
  double late_weight = 0.14338761;
  double critical_weight = 0.28618934;
  unsigned budget = 35;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
