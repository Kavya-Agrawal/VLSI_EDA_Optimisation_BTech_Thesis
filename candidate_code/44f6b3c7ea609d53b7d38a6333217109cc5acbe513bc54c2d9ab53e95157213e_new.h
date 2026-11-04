// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.73429819;
  double density_weight = 0.10722596;
  double prefix_weight = 0.19514478;
  double neighborhood_weight = 0.12540188;
  double late_weight = 0.14535343;
  double critical_weight = 0.06180062;
  unsigned budget = 20;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
