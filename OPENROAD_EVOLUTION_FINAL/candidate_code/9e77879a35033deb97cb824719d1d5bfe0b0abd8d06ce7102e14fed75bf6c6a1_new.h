// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.88852938;
  double density_weight = 0.56268385;
  double prefix_weight = 0.34903668;
  double neighborhood_weight = 0.29925103;
  double late_weight = 0.25522198;
  double critical_weight = 0.21414851;
  unsigned budget = 7;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
