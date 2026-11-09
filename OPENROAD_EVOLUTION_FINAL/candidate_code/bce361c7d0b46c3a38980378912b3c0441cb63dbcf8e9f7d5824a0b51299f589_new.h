// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31769972;
  double density_weight = 0.38366616;
  double prefix_weight = 0.07458497;
  double neighborhood_weight = 0.07920918;
  double late_weight = 0.01466547;
  double critical_weight = 0.02432839;
  unsigned budget = 24;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
