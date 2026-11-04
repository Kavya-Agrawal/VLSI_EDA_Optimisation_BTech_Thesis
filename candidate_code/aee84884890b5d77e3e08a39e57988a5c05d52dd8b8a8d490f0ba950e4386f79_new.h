// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23730274;
  double density_weight = 0.26428220;
  double prefix_weight = 0.21985295;
  double neighborhood_weight = 0.16390788;
  double late_weight = 0.23020688;
  double critical_weight = 0.06970438;
  unsigned budget = 33;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
