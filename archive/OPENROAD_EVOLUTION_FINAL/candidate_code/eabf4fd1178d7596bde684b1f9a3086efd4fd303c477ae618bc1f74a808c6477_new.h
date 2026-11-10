// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24723456;
  double density_weight = 0.35875913;
  double prefix_weight = 0.42923685;
  double neighborhood_weight = 0.19110208;
  double late_weight = 0.01568273;
  double critical_weight = 0.16211447;
  unsigned budget = 40;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
