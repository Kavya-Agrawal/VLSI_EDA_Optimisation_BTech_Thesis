// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90885080;
  double density_weight = 0.53237864;
  double prefix_weight = 0.07666322;
  double neighborhood_weight = 0.31260950;
  double late_weight = 0.22417082;
  double critical_weight = 0.29690865;
  unsigned budget = 14;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
