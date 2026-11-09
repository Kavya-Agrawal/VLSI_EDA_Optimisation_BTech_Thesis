// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.18826779;
  double density_weight = 0.29057408;
  double prefix_weight = 0.24665901;
  double neighborhood_weight = 0.22682763;
  double late_weight = 0.29409736;
  double critical_weight = 0.44309277;
  unsigned budget = 8;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
