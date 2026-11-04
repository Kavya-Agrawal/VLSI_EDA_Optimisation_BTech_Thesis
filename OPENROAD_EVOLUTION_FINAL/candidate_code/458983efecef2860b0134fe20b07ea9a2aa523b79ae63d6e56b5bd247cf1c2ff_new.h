// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66853700;
  double density_weight = 0.05268844;
  double prefix_weight = 0.10327768;
  double neighborhood_weight = 0.31192414;
  double late_weight = 0.25047738;
  double critical_weight = 0.02637179;
  unsigned budget = 5;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
