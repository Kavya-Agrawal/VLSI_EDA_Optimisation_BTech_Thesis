// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12089707;
  double density_weight = 0.48889184;
  double prefix_weight = 0.27155962;
  double neighborhood_weight = 0.00511290;
  double late_weight = 0.17511404;
  double critical_weight = 0.25663407;
  unsigned budget = 28;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
