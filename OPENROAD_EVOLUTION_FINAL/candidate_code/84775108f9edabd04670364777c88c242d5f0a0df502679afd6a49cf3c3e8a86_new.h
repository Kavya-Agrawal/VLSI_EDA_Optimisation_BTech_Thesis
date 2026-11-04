// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.53683816;
  double density_weight = 0.32156343;
  double prefix_weight = 0.12319099;
  double neighborhood_weight = 0.16550142;
  double late_weight = 0.10356664;
  double critical_weight = 0.28953331;
  unsigned budget = 24;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
