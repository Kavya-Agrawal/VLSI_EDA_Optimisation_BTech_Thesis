// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.11650467;
  double density_weight = 0.13846247;
  double prefix_weight = 0.32533857;
  double neighborhood_weight = 0.30120879;
  double late_weight = 0.22385026;
  double critical_weight = 0.38232772;
  unsigned budget = 19;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
