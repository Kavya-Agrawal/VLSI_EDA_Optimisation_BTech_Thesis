// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.53202050;
  double density_weight = 0.22532509;
  double prefix_weight = 0.28366218;
  double neighborhood_weight = 0.12259192;
  double late_weight = 0.14831738;
  double critical_weight = 0.06474969;
  unsigned budget = 19;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
